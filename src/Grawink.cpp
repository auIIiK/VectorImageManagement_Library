#include "../include/Grawink.h"

#include <map>
#include <string>

// Initialisation de l'instance à nullptr
GrawEditor* GrawEditor::instance = nullptr;

// Constructeur de GrawEditor(canva)
GrawEditor::GrawEditor(double width, double height, Color colorFond) : width(width), height(height), colorFond(colorFond) {}

// Creation de l'instance de GrawEditor (singleton)
GrawEditor& GrawEditor::GetEditor(double width, double height, Color colorFond) {
    if (instance == nullptr) {
        Logger::log("Creating instance of GrawEditor");
        instance = new GrawEditor(width, height, colorFond);
        atexit(&GrawEditor::DeleteInstance);
    }
    return *instance;
}

// Suppression de l'instance de GrawEditor
void GrawEditor::DeleteInstance() {
    Logger::log("Deleting instance of GrawEditor");
    delete instance;
    instance = nullptr;
}

// Méthode pour changer la taille du canva
GrawEditor& GrawEditor::Resize(double width, double height) {
    Logger::log("Resizing the canva to " + std::to_string(width) + "x" + std::to_string(height));
    this->width = width;
    this->height = height;
    return *this;
}

// Méthode pour changer la couleur de fond du canva
GrawEditor& GrawEditor::Repaint(Color colorFond) {
    Logger::log("Repainting the canva with color " + colorFond.RGBAtoString());
    this->colorFond = colorFond;
    return *this;
}

// Méthode qui reduit la taille du canav en supprimant les formes qui sont en dehors du canva
GrawEditor& GrawEditor::Crop(double width, double height) {
    Logger::log("Cropping the canva to " + std::to_string(width) + "x" + std::to_string(height));
    // Afficher la taille du canva avant le crop
    cout << "Taille du canva avant le crop : " << this->width << "x" << this->height << endl;
    //si une forme est en dehors du canva, on la supprime
    for (auto it = canva.begin(); it != canva.end(); ) {
        if ((*it)->isOutside(width, height)) {
            undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), (*it)->name, Action::ActionType::crop, this->width, this->height}));
            it = canva.erase(it);
        } else {
            ++it;
        }
    }   
    Resize(width, height);
    return *this;
}

// Méthode pour selection un ou des types de formes dans le canva afin d'afficher ou exporter uniquement ces formes
GrawEditor& GrawEditor::Select(ShapeType types) {
    Logger::log("Selecting shapes of type " + std::to_string(static_cast<uint64_t>(types)));
    for (auto& shape : canva) {
        shape->selected = (static_cast<uint64_t>(shape->type) & static_cast<uint64_t>(types)) != 0;
    }
    //Si la forme est dans la liste des undo et qu'elle n'est pas sélectionnée, on la selectionne
    for (auto& shape : undoList) {
        shape->shape->selected = (static_cast<uint64_t>(shape->shape->type) & static_cast<uint64_t>(types)) != 0;
    }
    //Si la forme est dans la liste des redo et qu'elle n'est pas sélectionnée, on la selectionne
    for (auto& shape : redoList) {
        shape->shape->selected = (static_cast<uint64_t>(shape->shape->type) & static_cast<uint64_t>(types)) != 0;
    }

    return *this;
}

// Méthode pour déselectionner un ou des types de formes dans le canva
GrawEditor& GrawEditor::Deselect(ShapeType types) {
    Logger::log("Deselecting shapes of type " + std::to_string(static_cast<uint64_t>(types)));
    for (auto& shape : canva) {
        shape->selected = (static_cast<uint64_t>(shape->type) & static_cast<uint64_t>(types)) == 0;
    }
    //Si la forme est dans la liste des undo et qu'elle est sélectionnée, on la déselectionne
    for (auto& shape : undoList) {
        shape->shape->selected = (static_cast<uint64_t>(shape->shape->type) & static_cast<uint64_t>(types)) == 0;
    }
    //Si la forme est dans la liste des redo et qu'elle est sélectionnée, on la déselectionne
    for (auto& shape : redoList) {
        shape->shape->selected = (static_cast<uint64_t>(shape->shape->type) & static_cast<uint64_t>(types)) == 0;
    }

    return *this;
}

// Méthode pour afficher les formes selectionnées dans le canva avec leurs informations dans la console
GrawEditor& GrawEditor::Print() {
    std::map<ShapeType, std::vector<Geom2D*>> categorizedShapes;

    // Catégorise les formes
    for (const auto& shape : canva) {
        if (shape->selected) {
            categorizedShapes[shape->type].push_back(shape.get());
        }
    }

    cout << "-------------------------------------" << endl;
    cout << "Forme selectioné dans le Canva: " << endl;

    // Imprime les formes dans l'ordre des types de formes
    for (const auto& pair : categorizedShapes) {
        cout << "+++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Type: " << static_cast<uint64_t>(pair.first) << endl;
        
        for (const auto& shape : pair.second) {
            shape->info();
        }
    }

    return *this;
}

// Méthode pour exporter les formes selectionnées dans le canva dans un fichier SVG
GrawEditor& GrawEditor::ExportSVG(const string& filename, bool PureSvg) {
    Logger::log("Exporting the canva to SVG file " + filename);
    SVGstream svg(filename, width, height, colorFond, PureSvg);
    for (const auto& shape : canva) {
        if (shape->selected) {
            svg << *shape;
        }
    }

    return *this;
}

// Méthode pour exporter les formes selectionnées dans le canva dans un fichier TikZ
GrawEditor& GrawEditor::ExportTikZ(const string& filename) {
    Logger::log("Exporting the canva to TikZ file " + filename);
    TikZstream tikz(filename, width, height, colorFond);
    for (const auto& shape : canva) {
        if (shape->selected) {
            tikz << *shape;
        }
    }

    return *this;
}

// Méthode qui vérifie si un point est dans une forme
bool GrawEditor::IsInShape(const string& name, Point point) {
    for (const auto& shape : canva) {
        if (shape->name == name) {
            return shape->isInside(point);
        }
    }
    return false;
}

// Méthode pour exporter les formes selectionnées dans le canva dans un fichier PPM (image binaire n'accpetant que les couleurs RGB)
GrawEditor& GrawEditor::ExportPPM(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    // Écrire l'en-tête PPM
    file << "P6\n" << width << " " << height << "\n255\n";

    // Écrire les pixels
    for (int y = 0; y < height; ++y) {
        cout << "Exportation en .ppm en cours..." << endl;
        cout << "Veuillez patientez..." <<endl;
        cout << "Ligne " << y << "/" << height << "\n" << endl;
        for (int x = 0; x < width; ++x) {
            Color color = colorFond;
            // Vérifier si une forme est présente à cet endroit
            for (const auto& shape : canva) { // Supposons que "shapes" est une liste de toutes vos formes
                if (IsInShape(shape->name, Point(x, y))) {
                    color = shape->getColorFond();
                    break;
                }
            }
            file << static_cast<char>(color.getRed())
                 << static_cast<char>(color.getGreen())
                 << static_cast<char>(color.getBlue());
        }
    }

    cout << "Exportation en .pam terminée \n\n" << endl;

    file.close();
    return *this;
}

// Méthode pour exporter les formes selectionnées dans le canva dans un fichier PAM (image binaire accpetant les couleurs RGB et Alpha)
GrawEditor& GrawEditor::ExportPAM(const std::string& filename) {

    std::ofstream file(filename, std::ios::binary);

    // Écrire l'en-tête PAM
    file << "P7\nWIDTH " << width << "\nHEIGHT " << height << "\nDEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n";

    // Écrire les pixels
    for (int y = 0; y < height; ++y) {
        cout << "Exportation en .pam en cours..." << endl;
        cout << "Veuillez patientez..." <<endl;
        cout << "Ligne " << y << "/" << height << "\n" << endl;  
        for (int x = 0; x < width; ++x) {
            Color color = colorFond;
            // Vérifier si une forme est présente à cet endroit
            for (const auto& shape : canva) { // Supposons que "shapes" est une liste de toutes vos formes
                if (IsInShape(shape->name, Point(x, y))) {
                    color = shape->getColorFond();
                    break;
                }
            }
            file << static_cast<char>(color.getRed())
                 << static_cast<char>(color.getGreen())
                 << static_cast<char>(color.getBlue())
                 << static_cast<char>(color.getAlpha()*255);
        }
    }

    cout << "Exportation en .pam terminée\n\n" << endl;

    file.close();
    return *this;

}

// Méthode pour supprimer une forme du canva
GrawEditor& GrawEditor::Delete(const string& name) {
    Logger::log("Deleting shape " + name);
    for (auto it = canva.begin(); it != canva.end(); ++it) {
        if ((*it)->name == name) {
            //Suprime la forme du canva de la list et l'ajoute à la liste undo avec l'action delete, et supprime la forme de la liste redo et undo si elle y est avec toute autre action que delete
            for (auto it = undoList.begin(); it != undoList.end(); ++it) {
                if ((*it)->name == name) {
                    undoList.erase(it);
                    break;
                }
            }
            for (auto it = redoList.begin(); it != redoList.end(); ++it) {
                if ((*it)->name == name) {
                    redoList.erase(it);
                    break;
                }
            }
            undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), name, Action::ActionType::Delete}));
            canva.erase(it);
            break;
        }
    }

    return *this;
}

// Méthode pour réaliser un redo sur la dernière action effectuée
GrawEditor& GrawEditor::Undo(int n) {
    Logger::log("Undoing " + std::to_string(n) + " actions");
    for(int i = 0; i < n; i++){
        if(undoList.empty()){
            return *this;
        }else{
            //si l'action est un add, on la supprime du canva et on l'ajoute à la liste redo avec l'action delete et on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::Add){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        canva.erase(it);
                        break;
                    }
                }
                redoList.push_back(std::make_unique<Action>(Action{undoList.back()->shape->clone(), undoList.back()->name, Action::ActionType::Delete}));
                undoList.pop_back();
            }else 
            //si l'action est un delete, on ajoute la forme au canva et on l'ajoute à la liste redo avec l'action add et on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::Delete){
                canva.push_back(undoList.back()->shape->clone());
                redoList.push_back(std::make_unique<Action>(Action{undoList.back()->shape->clone(), undoList.back()->name, Action::ActionType::Add}));
                undoList.pop_back();
            }else
            //si l'action est un rotate, on ajoute la forme canva a redo avec l'action rotate, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::Rotate){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        redoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), undoList.back()->name, Action::ActionType::Rotate}));
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(undoList.back()->shape->clone());
                undoList.pop_back();
                
            }else
            //si l'action est un translate, on ajoute la forme canva a redo avec l'action translate, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::Translate){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        redoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), undoList.back()->name, Action::ActionType::Translate}));
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(undoList.back()->shape->clone());
                undoList.pop_back();
            }else
            //si l'action est un scale, on ajoute la forme canva a redo avec l'action scale, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::Scale){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        redoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), undoList.back()->name, Action::ActionType::Scale}));
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(undoList.back()->shape->clone());
                undoList.pop_back();
            }else
            //si l'action est un fill, on ajoute la forme canva a redo avec l'action fill, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::fill){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        redoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), undoList.back()->name, Action::ActionType::fill}));
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(undoList.back()->shape->clone());
                undoList.pop_back();
            }else
            //si l'action est un contour, on ajoute la forme canva a redo avec l'action contour, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::contour){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        redoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), undoList.back()->name, Action::ActionType::contour}));
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(undoList.back()->shape->clone());
                undoList.pop_back();
            }else
            // si l'action est égale a other on ajoute la forme canva a redo avec l'action other, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::other){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == undoList.back()->name) {
                        redoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), undoList.back()->name, Action::ActionType::other}));
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(undoList.back()->shape->clone());
                undoList.pop_back();
            }
            // si l'action est égale a crop on redimensionne le canva avec les dimensions de l'action crop et on ajoute la forme canva a redo avec l'action crop, ont met la undo dans le canva et  on la supprime de la liste undo
            if(undoList.back()->ActionType == Action::ActionType::crop){
                double w = this->width;
                double h = this->height;
                Resize(undoList.back()->width, undoList.back()->height);

                // Supprimer toutes les formes de la liste undo avec l'action crop
                while(!undoList.empty() && undoList.back()->ActionType == Action::ActionType::crop){
                    // Ajouter la forme de l'action undo à la liste canva
                    canva.push_back(undoList.back()->shape->clone());

                    // Ajouter une seule forme à la liste redo avec la taille actuelle du canva avant le redimensionnement
                    redoList.push_back(std::make_unique<Action>(Action{canva.back()->clone(), canva.back()->name, Action::ActionType::crop, w, h}));

                    undoList.pop_back();
                }
            }

        }

    }

    return *this;
}

// Méthode pour effectuer un redo sur le undo effectué
GrawEditor& GrawEditor::Redo(int n) {
    Logger::log("Redoing " + std::to_string(n) + " actions");
    for(int i = 0; i < n; i++){
        if(redoList.empty()){
            return *this;
        }else{
            //si l'action est un add, on la supprime du canva et on l'ajoute à la liste undo avec l'action delete et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::Add){
                for (auto it = canva.begin(); it != canva.end(); ++it) {
                    if ((*it)->name == redoList.back()->name) {
                        canva.erase(it);
                        break;
                    }
                }
                undoList.push_back(std::make_unique<Action>(Action{redoList.back()->shape->clone(), redoList.back()->name, Action::ActionType::Delete}));
                redoList.pop_back();
            }else
            //si l'action est un delete, on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action add et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::Delete){
                canva.push_back(redoList.back()->shape->clone());
                undoList.push_back(std::make_unique<Action>(Action{redoList.back()->shape->clone(), redoList.back()->name, Action::ActionType::Add}));
                redoList.pop_back();
            }else
            //si l'action est un rotate, on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action rotate et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::Rotate){
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == redoList.back()->name){
                        undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), redoList.back()->name, Action::ActionType::Rotate}));
                        break;
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(redoList.back()->shape->clone());
                redoList.pop_back();
            }else
            //si l'action est un translate, on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action translate et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::Translate){
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == redoList.back()->name){
                        undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), redoList.back()->name, Action::ActionType::Translate}));
                        break;
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(redoList.back()->shape->clone());
                redoList.pop_back();
            }else
            //si l'action est un scale, on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action scale et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::Scale){
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == redoList.back()->name){
                        undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), redoList.back()->name, Action::ActionType::Scale}));
                        break;
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(redoList.back()->shape->clone());
                redoList.pop_back();
            }else
            //si l'action est un fill, on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action fill et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::fill){
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == redoList.back()->name){
                        undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), redoList.back()->name, Action::ActionType::fill}));
                        break;
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(redoList.back()->shape->clone());
                redoList.pop_back();
            }else
            //si l'action est un contour, on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action contour et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::contour){
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == redoList.back()->name){
                        undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), redoList.back()->name, Action::ActionType::contour}));
                        break;
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(redoList.back()->shape->clone());
                redoList.pop_back();
            }else
            // si l'action est égale a other on ajoute la forme au canva et on l'ajoute à la liste undo avec l'action other et on la supprime de la liste redo
            if(redoList.back()->ActionType == Action::ActionType::other){
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == redoList.back()->name){
                        undoList.push_back(std::make_unique<Action>(Action{(*it)->clone(), redoList.back()->name, Action::ActionType::other}));
                        break;
                    }
                }
                //Suprimmer la forme dans la liste canva 
                for(auto it = canva.begin(); it != canva.end(); ++it){
                    if((*it)->name == undoList.back()->name){
                        canva.erase(it);
                        break;
                    }
                }
                canva.push_back(redoList.back()->shape->clone());
                redoList.pop_back();
            }else
            if(!redoList.empty() && redoList.back()->ActionType == Action::ActionType::crop){
                double w = redoList.back()->width;
                double h = redoList.back()->height;

                // Supprimer toutes les formes de la liste redo avec l'action crop
                while(!redoList.empty() && redoList.back()->ActionType == Action::ActionType::crop){
                    redoList.pop_back();
                }
            
                // Appeler la méthode crop avec les paramètres appropriés
                Crop(w, h);
            
            }

        }

    }

    return *this;
}

// Méthode pour appeler la méthode rotate d'une forme dans le canva
GrawEditor& GrawEditor::Rotate(const string& name, int angle) {
    //Si la forme est dans le canva on l'ajoute à la liste undo avec l'action rotate et on la rotate dans le canva
    for (auto& shape : canva) {
        if (shape->name == name) {
            undoList.push_back(std::make_unique<Action>(Action{shape->clone(), name, Action::ActionType::Rotate}));
            shape->rotation(angle);
            break;
        }
    }
    return *this;
}
// Méthode pour appeler la méthode translate d'une forme dans le canva
GrawEditor& GrawEditor::Translate(const string& name, int x, int y) {
    //Si la forme est dans le canva on l'ajoute à la liste undo avec l'action translate et on la translate dans le canva
    for (auto& shape : canva) {
        if (shape->name == name) {
            undoList.push_back(std::make_unique<Action>(Action{shape->clone(), name, Action::ActionType::Translate}));
            shape->translation(x, y);
            break;
        }
    }
    return *this;
}
// Méthode pour appeler la méthode scale d'une forme dans le canva
GrawEditor& GrawEditor::Scale(const string& name, double scaleFactor) {
    //Si la forme est dans le canva on l'ajoute à la liste undo avec l'action scale et on la scale dans le canva
    for (auto& shape : canva) {
        if (shape->name == name) {
            undoList.push_back(std::make_unique<Action>(Action{shape->clone(), name, Action::ActionType::Scale}));
            shape->scaling(scaleFactor);
            break;
        }
    }
    return *this;
}
// Méthode pour appeler la méthode fill d'une forme dans le canva
GrawEditor& GrawEditor::Fill(const string& name, Color color) {
    //Si la forme est dans le canva on l'ajoute à la liste undo avec l'action fill et on la fill dans le canva
    for (auto& shape : canva) {
        if (shape->name == name) {
            undoList.push_back(std::make_unique<Action>(Action{shape->clone(), name, Action::ActionType::fill}));
            shape->fill(color);
            break;
        }
    }
    return *this;
}
// Méthode pour appeler la méthode contour d'une forme dans le canva
GrawEditor& GrawEditor::Contour(const string& name, Color color) {
    //Si la forme est dans le canva on l'ajoute à la liste undo avec l'action contour et on la contour dans le canva
    for (auto& shape : canva) {
        if (shape->name == name) {
            undoList.push_back(std::make_unique<Action>(Action{shape->clone(), name, Action::ActionType::contour}));
            shape->contour(color);
            break;
        }
    }
    return *this;
}

// Méthode pour rajouter un point à un polygone
GrawEditor& GrawEditor::AddPointPolygon(const string& name, Point point) {
    for (auto& shape : canva) {
        if (shape->name == name) {
            Polygon* polygon = dynamic_cast<Polygon*>(shape.get());
            if (polygon != nullptr) {
                // Créez une copie du polygone avant de le modifier
                auto polygonCopy = std::make_unique<Polygon>(*polygon);
                
                // Ajoutez un point au Polygon
                polygon->addPoint(point);

                // Ajoutez la copie du polygone à la pile d'annulation
                undoList.push_back(std::make_unique<Action>(Action{std::move(polygonCopy), name, Action::ActionType::other}));
            } else {
                std::cerr << "Impossible d'ajouter un point à une forme qui n'est pas un polygone" << std::endl;
            }
        }
    }
    
    return *this;
}
//Méthode pour supprimer un point d'un polygone
GrawEditor& GrawEditor::RemovePointPolygon(const std::string& name, int indexPoint){
    for (auto& shape : canva) {
        if (shape->name == name) {
            Polygon* polygon = dynamic_cast<Polygon*>(shape.get());
            if (polygon != nullptr) {
                // Créez une copie du polygone avant de le modifier
                auto polygonCopy = std::make_unique<Polygon>(*polygon);

                // Supprimez un point du Polygon
                polygon->removePoint(indexPoint);

                // Ajoutez la copie du polygone à la pile d'annulation
                undoList.push_back(std::make_unique<Action>(Action{std::move(polygonCopy), name, Action::ActionType::other}));
            } else {
                std::cerr << "Impossible de supprimer un point à une forme qui n'est pas un polygone" << std::endl;
            }
        }
    }
    
    return *this;
}

//Méthode pour extraire les valeurs RGBA d'une chaine de caractère
std::vector<double> extractRGBA(const std::string& rgba) {
    std::vector<double> result;
    std::string number;
    bool decimal = false;
    for (char c : rgba) {
        if (std::isdigit(c) || c == '.') {
            if (c == '.') decimal = true;
            number += c;
        } else if (c == ',' || c == ')') {
            if (decimal) {
                result.push_back(std::stod(number));
                decimal = false;
            } else {
                result.push_back(static_cast<double>(std::stoi(number)));
            }
            number.clear();
        }
    }
    return result;
}
//Méthode pour convertir une chaine de caractère en double
double stringToDouble(const std::string& s) {
    try {
        return std::stod(s);
    } catch (std::invalid_argument&) {
        std::cerr << "Invalid argument: " << s << std::endl;
        return 0.0;
    }
}
//Méthode pour creer des noms de formes uniques
std::map<std::string, int> formCounters;
std::string createFormName(const std::string& baseName) {
    // Si la baseName n'est pas encore dans le map, elle sera ajoutée avec une valeur initiale de 0
    int& counter = formCounters[baseName];
    counter++;
    return baseName + std::to_string(counter);
}

// Méthode pour charger un fichier SVG
GrawEditor& GrawEditor::LoadSVG(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
      std::cerr << "Failed to open file: " << filename << std::endl;
      return *this;
  }


  std::string current_rect;
  std::string current_circle;
  std::string current_ellipse;
  std::string current_text;
  std::regex rect_start_regex(R"(<rect\s+)");
  std::regex rect_end_regex(R"(.*?/>)");
  std::regex circle_start_regex(R"(<circle\s+)");
  std::regex circle_end_regex(R"(.*?/>)");
  std::regex ellipse_start_regex(R"(<ellipse\s+)");
  std::regex ellipse_end_regex(R"(.*?/>)");
  std::regex text_start_regex(R"(<text\s+)");
  std::regex text_end_regex(R"(<\/text>)");
  std::regex polygon_start_regex(R"(<polygon\s+)");
  std::regex polygon_end_regex(R"(.*?/>)");
  std::regex line_start_regex(R"(<line\s+)");
  std::regex line_end_regex(R"(.*?/>)");
  std::regex attr_regex(R"(([\w-]+)=\"([^\"]*)\")");
  std::smatch match;

  // Lire toutes les lignes du fichier dans un vector
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
      lines.push_back(line);
  }

  // Parcours du vector pour traiter les <line>
    for (size_t i = 0; i < lines.size(); ++i) {
        // Chercher un <line>
        if (std::regex_search(lines[i], match, line_start_regex)) {
            // Commence un nouveau <line>
            current_rect = lines[i];
            if (!std::regex_search(lines[i], match, line_end_regex)) {
                // Continue de lire jusqu'à la fin du <line>
                for (++i; i < lines.size(); ++i) {
                    current_rect += lines[i];
                    if (std::regex_search(lines[i], match, line_end_regex)) {
                        break;
                    }
                }
            }
    
            // Extraire les attributs du <line>
            std::smatch attr_match;
            std::map<std::string, std::string> attrs;
    
            while (std::regex_search(current_rect, attr_match, attr_regex)) {
                attrs[attr_match[1].str()] = attr_match[2].str();
                current_rect = attr_match.suffix().str();
            }
    
            // Extraire les attributs nécessaires
            // x1, y1, x2, y2, stroke
            double x1 = stringToDouble(attrs["x1"]);
            double y1 = stringToDouble(attrs["y1"]);
            double x2 = stringToDouble(attrs["x2"]);
            double y2 = stringToDouble(attrs["y2"]);
            std::vector<double> strokeRGBA = extractRGBA(attrs["stroke"]);
            std::string transform = attrs["transform"];
    
            // Créer un nouveau Line
            Color strokeColor(static_cast<uint8_t>(strokeRGBA[0]), static_cast<uint8_t>(strokeRGBA[1]), static_cast<uint8_t>(strokeRGBA[2]), static_cast<float>(strokeRGBA[3]));
            std::string name = createFormName("line");
            this->Add<Stroke>(name, Point(static_cast<int>(x1), static_cast<int>(y1)), Point(static_cast<int>(x2), static_cast<int>(y2)), strokeColor);

            // Appliquer la transformation
            std::istringstream transformStream(transform);
            std::string transformWord;

            if(transform != ""){
                while (std::getline(transformStream, transformWord, ' ')) {
                    if (transformWord.find("rotate") != std::string::npos) {
                        // Extraire l'angle de rotation
                        std::string angle = transformWord.substr(transformWord.find("(") + 1, transformWord.find(")") - transformWord.find("(") - 1);
                        this->Rotate(name, static_cast<int>(stringToDouble(angle)));
                    } 
                }
            }
        }
    }




  // Parcours du vector pour traiter les <rect>
  for (size_t i = 0; i < lines.size(); ++i) {
    // Chercher un <rect>
    if (std::regex_search(lines[i], match, rect_start_regex)) {
        // Commence un nouveau <rect>
        current_rect = lines[i];
        if (!std::regex_search(lines[i], match, rect_end_regex)) {
            // Continue de lire jusqu'à la fin du <rect>
            for (++i; i < lines.size(); ++i) {
                current_rect += lines[i];
                if (std::regex_search(lines[i], match, rect_end_regex)) {
                    break;
                }
            }
        }

        // Extraire les attributs du <rect>
        std::smatch attr_match;
        std::map<std::string, std::string> attrs;

        while (std::regex_search(current_rect, attr_match, attr_regex)) {
            attrs[attr_match[1].str()] = attr_match[2].str();
            current_rect = attr_match.suffix().str();
        }

        // Extraire les attributs nécessaires
        // x, y, width, height, fill, stroke, transform
        double x = stringToDouble(attrs["x"]);
        double y = stringToDouble(attrs["y"]);
        double width = stringToDouble(attrs["width"]);
        double height = stringToDouble(attrs["height"]);
        std::vector<double> fillRGBA = extractRGBA(attrs["fill"]);
        std::vector<double> strokeRGBA = extractRGBA(attrs["stroke"]);
        std::string transform = attrs["transform"];

        // Créer un nouveau Rectangle
        Color fillColor(static_cast<uint8_t>(fillRGBA[0]), static_cast<uint8_t>(fillRGBA[1]), static_cast<uint8_t>(fillRGBA[2]), static_cast<float>(fillRGBA[3]));
        Color strokeColor(static_cast<uint8_t>(strokeRGBA[0]), static_cast<uint8_t>(strokeRGBA[1]), static_cast<uint8_t>(strokeRGBA[2]), static_cast<float>(strokeRGBA[3]));
        std::string name = createFormName("rectangle");
        this->Add<Rectangle>(name, Point(static_cast<int>(x), static_cast<int>(y)), height, width, fillColor, strokeColor);

        // Appliquer la transformation
        std::istringstream transformStream(transform);
        std::string transformWord;

        while (std::getline(transformStream, transformWord, ' ')) {
            if (transformWord.find("rotate") != std::string::npos) {
                // Extraire l'angle de rotation
                std::string angle = transformWord.substr(transformWord.find("(") + 1, transformWord.find(")") - transformWord.find("(") - 1);
                this->Rotate(name, static_cast<int>(stringToDouble(angle)));
            } 
        }
    }
  }

  // Parcours du vector pour traiter les <circle>
  for(size_t i = 0; i < lines.size(); ++i){
    // Chercher un <circle>
    if (std::regex_search(lines[i], match, circle_start_regex)) {
        // Commence un nouveau <circle>
        current_circle = lines[i];
        if (!std::regex_search(lines[i], match, circle_end_regex)) {
            // Continue de lire jusqu'à la fin du <circle>
            for (++i; i < lines.size(); ++i) {
                current_circle += lines[i];
                if (std::regex_search(lines[i], match, circle_end_regex)) {
                    break;
                }
            }
        }

        // Extraire les attributs du <circle>
        std::smatch attr_match;
        std::map<std::string, std::string> attrs;

        while (std::regex_search(current_circle, attr_match, attr_regex)) {
            attrs[attr_match[1].str()] = attr_match[2].str();
            current_circle = attr_match.suffix().str();
        }

        // Extraire les attributs nécessaires
        // cx, cy, r, fill, stroke
        double cx = stringToDouble(attrs["cx"]);
        double cy = stringToDouble(attrs["cy"]);
        double r = stringToDouble(attrs["r"]);
        std::vector<double> fillRGBA = extractRGBA(attrs["fill"]);
        std::vector<double> strokeRGBA = extractRGBA(attrs["stroke"]);

        // Créer un nouveau Circle
        Color fillColor(static_cast<uint8_t>(fillRGBA[0]), static_cast<uint8_t>(fillRGBA[1]), static_cast<uint8_t>(fillRGBA[2]), static_cast<float>(fillRGBA[3]));
        Color strokeColor(static_cast<uint8_t>(strokeRGBA[0]), static_cast<uint8_t>(strokeRGBA[1]), static_cast<uint8_t>(strokeRGBA[2]), static_cast<float>(strokeRGBA[3]));
        std::string name = createFormName("circle");
        this->Add<Disc>(name, Point(static_cast<int>(cx), static_cast<int>(cy)), fillColor, strokeColor, r);
    }
  }

  // Parcours du vector pour traiter les <ellipse>
  for(size_t i = 0; i < lines.size(); ++i){
    // Chercher un <ellipse>
    if (std::regex_search(lines[i], match, ellipse_start_regex)) {
        // Commence un nouveau <ellipse>
        current_ellipse = lines[i];
        if (!std::regex_search(lines[i], match, ellipse_end_regex)) {
            // Continue de lire jusqu'à la fin du <ellipse>
            for (++i; i < lines.size(); ++i) {
                current_ellipse += lines[i];
                if (std::regex_search(lines[i], match, ellipse_end_regex)) {
                    break;
                }
            }
        }

        // Extraire les attributs du <ellipse>
        std::smatch attr_match;
        std::map<std::string, std::string> attrs;

        while (std::regex_search(current_ellipse, attr_match, attr_regex)) {
            attrs[attr_match[1].str()] = attr_match[2].str();
            current_ellipse = attr_match.suffix().str();
        }

        // Extraire les attributs nécessaires
        // cx, cy, rx, ry, fill, stroke, transform
        double cx = stringToDouble(attrs["cx"]);
        double cy = stringToDouble(attrs["cy"]);
        double rx = stringToDouble(attrs["rx"]);
        double ry = stringToDouble(attrs["ry"]);
        std::vector<double> fillRGBA = extractRGBA(attrs["fill"]);
        std::vector<double> strokeRGBA = extractRGBA(attrs["stroke"]);
        std::string transform = attrs["transform"];

        // Créer un nouveau Ellipse
        Color fillColor(static_cast<uint8_t>(fillRGBA[0]), static_cast<uint8_t>(fillRGBA[1]), static_cast<uint8_t>(fillRGBA[2]), static_cast<float>(fillRGBA[3]));
        Color strokeColor(static_cast<uint8_t>(strokeRGBA[0]), static_cast<uint8_t>(strokeRGBA[1]), static_cast<uint8_t>(strokeRGBA[2]), static_cast<float>(strokeRGBA[3]));
        std::string name = createFormName("ellipse");
        this->Add<Ellipse>(name, Point(static_cast<int>(cx), static_cast<int>(cy)), fillColor, strokeColor, rx, ry);

        // Appliquer la transformation
        std::istringstream transformStream(transform);
        std::string transformWord;

        while (std::getline(transformStream, transformWord, ' ')) {
            if (transformWord.find("rotate") != std::string::npos) {
                // Extraire l'angle de rotation
                std::string angle = transformWord.substr(transformWord.find("(") + 1, transformWord.find(")") - transformWord.find("(") - 1);
                this->Rotate(name, static_cast<int>(stringToDouble(angle)));
            }
        }
    }
  }

  // Parcours du vector pour traiter les <text>
  for(size_t i = 0; i < lines.size(); ++i){
    // Chercher un <text>
    if (std::regex_search(lines[i], match, text_start_regex)) {
        // Commence un nouveau <text>
        current_text = lines[i];
        if (!std::regex_search(lines[i], match, text_end_regex)) {
            // Continue de lire jusqu'à la fin du <text>
            for (++i; i < lines.size(); ++i) {
                current_text += lines[i];
                if (std::regex_search(lines[i], match, text_end_regex)) {
                    break;
                }
            }
        }

        // Extraire les attributs du <text>
        std::string original_text = current_text;
        std::smatch attr_match;
        std::map<std::string, std::string> attrs;

        while (std::regex_search(current_text, attr_match, attr_regex)) {
            attrs[attr_match[1].str()] = attr_match[2].str();
            current_text = attr_match.suffix().str();
        }

        // Extraire les attributs nécessaires
        // x, y, font-size, font-family, fill, stroke, transform
        double x = stringToDouble(attrs["x"]);
        double y = stringToDouble(attrs["y"]);
        double fontSize = stringToDouble(attrs["font-size"]);
        if(attrs.find("stroke-width") == attrs.end()){
            attrs["stroke-width"] = "0";
        }
        double thickness = stringToDouble(attrs["stroke-width"]);
        std::string fontFamily = attrs["font-family"];
        std::vector<double> fillRGBA = extractRGBA(attrs["fill"]);
        std::vector<double> strokeRGBA = extractRGBA(attrs["stroke"]);
        std::string transform = attrs["transform"];
        // Extraire le contenu de la balise <text>
        std::string text_content;
        std::regex text_content_regex(R"(<text.*?>([\s\S]*?)</text>)");
        std::smatch text_content_match;
        if (std::regex_search(original_text, text_content_match, text_content_regex)) {
          text_content = text_content_match[1].str();
          // text_content contient maintenant le texte
        }


        // Créer un nouveau Text
        Color fillColor(static_cast<uint8_t>(fillRGBA[0]), static_cast<uint8_t>(fillRGBA[1]), static_cast<uint8_t>(fillRGBA[2]), static_cast<float>(fillRGBA[3]));
        Color strokeColor(static_cast<uint8_t>(strokeRGBA[0]), static_cast<uint8_t>(strokeRGBA[1]), static_cast<uint8_t>(strokeRGBA[2]), static_cast<float>(strokeRGBA[3]));
        std::string name = createFormName("text");
        this->Add<Text>(name, text_content, fontFamily, fontSize, thickness, fillColor, strokeColor, Point(static_cast<int>(x), static_cast<int>(y)));

        // Appliquer la transformation
        std::istringstream transformStream(transform);
        std::string transformWord;

        while (std::getline(transformStream, transformWord, ' ')) {
            if (transformWord.find("rotate") != std::string::npos) {
                // Extraire l'angle de rotation
                std::string angle = transform == "rotate(" ? "0" : transformWord.substr(transformWord.find("(") + 1, transformWord.find(")") - transformWord.find("(") - 1);
                this->Rotate(name, static_cast<int>(stringToDouble(angle)));
            }
        }
    }
  }

  // Parcours du vector pour traiter les <polygon>
  for(size_t i = 0; i < lines.size(); ++i){
    // Chercher un <polygon>
    if (std::regex_search(lines[i], match, polygon_start_regex)) {
        // Commence un nouveau <polygon>
        current_text = lines[i];
        if (!std::regex_search(lines[i], match, polygon_end_regex)) {
            // Continue de lire jusqu'à la fin du <polygon>
            for (++i; i < lines.size(); ++i) {
                current_text += lines[i];
                if (std::regex_search(lines[i], match, polygon_end_regex)) {
                    break;
                }
            }
        }

        // Extraire les attributs du <polygon>
        std::string original_text = current_text;
        std::smatch attr_match;
        std::map<std::string, std::string> attrs;

        while (std::regex_search(current_text, attr_match, attr_regex)) {
            attrs[attr_match[1].str()] = attr_match[2].str();
            current_text = attr_match.suffix().str();
        }

        // Extraire les attributs nécessaires
        // points, fill, stroke, transform
        std::string points = attrs["points"];
        std::vector<double> fillRGBA = extractRGBA(attrs["fill"]);
        std::vector<double> strokeRGBA = extractRGBA(attrs["stroke"]);
        std::string transform = attrs["transform"];

        // Créer un nouveau Polygon
        Color fillColor(static_cast<uint8_t>(fillRGBA[0]), static_cast<uint8_t>(fillRGBA[1]), static_cast<uint8_t>(fillRGBA[2]), static_cast<float>(fillRGBA[3]));
        Color strokeColor(static_cast<uint8_t>(strokeRGBA[0]), static_cast<uint8_t>(strokeRGBA[1]), static_cast<uint8_t>(strokeRGBA[2]), static_cast<float>(strokeRGBA[3]));
        std::string name = createFormName("polygon");
        this->Add<Polygon>(name, fillColor, strokeColor);

        // Extraire les points du <polygon>
        std::istringstream pointsStream(points);
        std::string point;
        while (std::getline(pointsStream, point, ' ')) {
            std::istringstream pointStream(point);
            std::string x, y;
            std::getline(pointStream, x, ',');
            std::getline(pointStream, y, ',');
            this->AddPointPolygon(name, Point(static_cast<int>(stringToDouble(x)), static_cast<int>(stringToDouble(y))));
        }


        

        // Appliquer la transformation
        std::istringstream transformStream(transform);
        std::string transformWord;

        while (std::getline(transformStream, transformWord, ' ')) {
            if (transformWord.find("rotate") != std::string::npos) {
                // Extraire l'angle de rotation
                std::string angle = transform == "rotate(" ? "0" : transformWord.substr(transformWord.find("(") + 1, transformWord.find(")") - transformWord.find("(") - 1);
                this->Rotate(name, static_cast<int>(stringToDouble(angle)));
            }
        }

    }

  }

    return *this;

}
