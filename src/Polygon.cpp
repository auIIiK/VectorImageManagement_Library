#include "../include/Polygon.h"

using namespace std;

/* Constructeur */
//Constructeur par initialisation
Polygon::Polygon(Color colorFond, Color colorBorder){

    this->selected = false;
    this->tabPoints = std::make_shared<ReallocatablePointsArray>();
    if(this->tabPoints != nullptr){
        this->type = Polygon::getType();
    }
    this->colorFond = colorFond;
    this->colorBorder = colorBorder;
    this->rotationAngle = 0;
    Logger::log("Constructeur par initialisation du Polygon de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorBorder.RGBAtoString() + ").");
};
// Constructeur par copie
Polygon::Polygon(const Polygon &p) : ReallocatablePointsArray(p){
    this->name = p.name;
    this->selected = p.selected;
    this->type = p.type;
    // Faire une copie profonde du tableau de points
    this->tabPoints = std::make_shared<ReallocatablePointsArray>(*p.tabPoints);
    this->colorFond = p.colorFond;
    this->colorBorder = p.colorBorder;
    this->rotationAngle = p.rotationAngle;
    Logger::log("Constructeur par copie du Polygon de nom : " + p.name + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorBorder.RGBAtoString() + ").");
};
// Opérateur d'assignation
Polygon& Polygon::operator=(const Polygon &p){
    if(this != &p){
        this->name = p.name;
        this->selected = p.selected;
        this->type = p.type;
        this->tabPoints = p.tabPoints;
        this->colorFond = p.colorFond;
        this->colorBorder = p.colorBorder;
        this->rotationAngle = p.rotationAngle;
    }   
    Logger::log("Opérateur d'assignation du Polygon de nom : " + p.name + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorBorder.RGBAtoString() + ").");
    return *this;
};


/* Destructeur */
Polygon::~Polygon(){
    Logger::log("Destructeur du Polygon de nom : " + this->name + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorBorder.RGBAtoString() + ").");
};

/* Méthodes */
//getters
std::shared_ptr<ReallocatablePointsArray> Polygon::getTabPoint() const {
    return this->tabPoints;
}
Color Polygon::getColorFond(){
    return this->colorFond;
}
Color Polygon::getColorContour(){
    return this->colorBorder;
}
//Aire du polygon
double Polygon::aire(){
    double aire = 0;
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        if(i == this->getTabPoint()->getTailleTab() - 1){
            aire += (this->getTabPoint()->getPoint(i)->getAbs() * this->getTabPoint()->getPoint(0)->getOrd()) - (this->getTabPoint()->getPoint(i)->getAbs() * this->getTabPoint()->getPoint(0)->getOrd());
        }
        else{
            aire += (this->getTabPoint()->getPoint(i)->getAbs() * this->getTabPoint()->getPoint(i+1)->getOrd()) - (this->getTabPoint()->getPoint(i)->getAbs() * this->getTabPoint()->getPoint(i+1)->getOrd());
        }
    }
    if(aire < 0){
        aire = -aire;
    }
    aire = (aire) / 2;
    return aire;
}

//ShapetypeToString
std::string Polygon::ShapeTypeToString(ShapeType type){
    switch(type){
        case ShapeType::Triangle:
            return "Triangle";
            break;
        case ShapeType::Rectangle:
            return "Rectangle";
            break;
        case ShapeType::Pentagon:
            return "Pentagon";
            break;
        case ShapeType::Hexagon:
            return "Hexagon";
            break;
        case ShapeType::Heptagon:
            return "Heptagon";
            break;
        case ShapeType::Octogon:
            return "Octogon";
            break;
        case ShapeType::Complexe:
            return "Complexe";
            break;
        case ShapeType::Stroke:
            return "Stroke";
            break;
        default:
            return "Unknown";
            break;
    }
}

//Information du polygon
void Polygon::info(){
    cout << "Caractéristique du polygon : " << endl;
    cout << "ShapeType : " << this->ShapeTypeToString(getType()) << endl;
    cout << "Name : " << this->name << endl;
    cout << "Nombre de point du polygon : " << this->getTabPoint()->getTailleTab() << endl;
    cout << "Liste des points du polygon : " << endl;
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        cout << "Point " << i << " : " << this->getTabPoint()->getPoint(i)->getAbs() << " " << this->getTabPoint()->getPoint(i)->getOrd() << endl;
    }
    cout << "Aire du polygon : " << this->aire() << endl;
    cout << "Couleur du remplissage du polygon : " << this->getColorFond().RGBAtoString() << endl;
    cout << "Couleur du contour du polygon : " << this->getColorContour().RGBAtoString() << endl;
    cout << "Selected : " << this->selected << endl;
};
//Type du polygon
Polygon::ShapeType Polygon::getType(){
    //Si il a plus de 5 points, c'est un pentagone, si il a 4 points, c'est un carré, si il a 3 points, c'est un triangle, si il a 2 points, c'est un stroke, si 6 points, c'est un hexagone, si 7 points, c'est un heptagone, si 8 points, c'est un octogone, sinon c'est un Complexe
    if(this->getTabPoint()->getTailleTab() == 5){
        return ShapeType::Pentagon;
    }
    else if(this->getTabPoint()->getTailleTab() == 4){
        return ShapeType::Rectangle;
    }
    else if(this->getTabPoint()->getTailleTab() == 3){
        return ShapeType::Triangle;
    }
    else if(this->getTabPoint()->getTailleTab() == 2){
        return ShapeType::Stroke;
    }
    else if(this->getTabPoint()->getTailleTab() == 6){
        return ShapeType::Hexagon;
    }
    else if(this->getTabPoint()->getTailleTab() == 7){
        return ShapeType::Heptagon;
    }
    else if(this->getTabPoint()->getTailleTab() == 8){
        return ShapeType::Octogon;
    }
    else{
        return ShapeType::Complexe;
    }
}
//Clone l'objet
std::unique_ptr<Geom2D> Polygon::clone() const{
    return std::make_unique<Polygon>(*this);
}
//Vérifie si le polygon est en dehors du canva
bool Polygon::isOutside(double width, double height){
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        if(this->getTabPoint()->getPoint(i)->getAbs() < 0 || this->getTabPoint()->getPoint(i)->getAbs() > width || this->getTabPoint()->getPoint(i)->getOrd() < 0 || this->getTabPoint()->getPoint(i)->getOrd() > height){
            return true;
        }
    }
    return false;
}
//Vérifie si un point est dans le polygon
bool Polygon::isInside(Point point){
    int i, j;
    bool c = false;
    for (i = 0, j = this->getTabPoint()->getTailleTab()-1; i < this->getTabPoint()->getTailleTab(); j = i++) {
        if ( ((this->getTabPoint()->getPoint(i)->getOrd()>point.getOrd()) != (this->getTabPoint()->getPoint(j)->getOrd()>point.getOrd())) &&
         (point.getAbs() < (this->getTabPoint()->getPoint(j)->getAbs()-this->getTabPoint()->getPoint(i)->getAbs()) * (point.getOrd()-this->getTabPoint()->getPoint(i)->getOrd()) / (this->getTabPoint()->getPoint(j)->getOrd()-this->getTabPoint()->getPoint(i)->getOrd()) + this->getTabPoint()->getPoint(i)->getAbs()) )
        c = !c;
    }
    return c;
}
//Surchage de l'opérateur <<
SVGstream& operator<<(SVGstream &os, const Polygon &p){
    //Avec la rotation
    if(p.rotationAngle != 0){
        os << "\n<polygon points=\"";
        for(int i = 0; i < p.getTabPoint()->getTailleTab(); i++){
            os << p.getTabPoint()->getPoint(i)->getAbs() << "," << p.getTabPoint()->getPoint(i)->getOrd() << " ";
        }
        os << "\" fill=\"RGBA(" << p.colorFond.RGBAtoString() << ")\" stroke=\"RGBA(" << p.colorBorder.RGBAtoString() << ")\" transform=\"rotate(" << p.rotationAngle << " " << p.rotationCenter.getAbs() << " " << p.rotationCenter.getOrd() << ")\" />";
    }
    else{
        os << "\n<polygon points=\"";
        for(int i = 0; i < p.getTabPoint()->getTailleTab(); i++){
            os << p.getTabPoint()->getPoint(i)->getAbs() << "," << p.getTabPoint()->getPoint(i)->getOrd() << " ";
        }
        os << "\" fill=\"RGBA(" << p.colorFond.RGBAtoString() << ")\" stroke=\"RGBA(" << p.colorBorder.RGBAtoString() << ")\" />";
    }
    return os;
}
//print
void Polygon::print(SVGstream& os){
    Logger::log("Print du polygon.");
    os << *this;
}
//printTikZ
void Polygon::printTikZ(TikZstream& os){
    Logger::log("PrintTikZ du polygon.");
    os << "\n\\draw[fill={rgb:red," << this->colorFond.getRed()
       << ";green," << this->colorFond.getGreen()
       << ";blue," << this->colorFond.getBlue() 
       << "}, opacity=" << this->colorFond.getAlpha() 
       << "] ";
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        os << "(" << this->getTabPoint()->getPoint(i)->getAbs() << "," << this->getTabPoint()->getPoint(i)->getOrd() << ") -- ";
    }
    os << "cycle;\n";
}

//Centre du polygon
Point Polygon::center(){
    int cx = 0;
    int cy = 0;
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        cx += this->getTabPoint()->getPoint(i)->getAbs();
        cy += this->getTabPoint()->getPoint(i)->getOrd();
    }
    cx = cx / this->getTabPoint()->getTailleTab();
    cy = cy / this->getTabPoint()->getTailleTab();
    Point center(cx, cy);
    return center;
}
//Rajout de points
void Polygon::addPoint(const Point p){
    Logger::log("Ajout d'un point au polygon de nom : " + this->name + ".");
    this->getTabPoint()->addPoint(p);
    //mise a jour de ShapeType
    this->type = Polygon::getType();
    // Mise a jour du centre de rotation
    this->rotationCenter = this->center();
}
//Suppression de points
void Polygon::removePoint(const int i){
    Logger::log("Suppression d'un point du polygon de nom : " + this->name + ".");
    this->getTabPoint()->removePoint(i);
    //mise a jour de ShapeType
    this->type = Polygon::getType();
    // Mise a jour du centre de rotation
    this->rotationCenter = this->center();
}

/* Méthode virtuelles pures */
// Translation
void Polygon::translation(const int x, const int y){
    Logger::log("Translation du polygon de nom : " + name + " de (" + to_string(this->center().getAbs()) + "," + to_string(this->center().getOrd()) + ") à (" + to_string(this->center().getAbs()+x) + "," + to_string(this->center().getOrd()+y) + ").");
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        this->getTabPoint()->getPoint(i)->setAbs(this->getTabPoint()->getPoint(i)->getAbs() + x);
        this->getTabPoint()->getPoint(i)->setOrd(this->getTabPoint()->getPoint(i)->getOrd() + y);
    }
    // Mise à jour du centre de rotation
    this->rotationCenter = this->center();
}
// Rotation
void Polygon::rotation(const int angle){
    Logger::log("Rotation du polygon de nom : " + name + " de " + to_string(this->rotationAngle) + "° à " + to_string(this->rotationAngle+angle) + "°.");
    // Calculer le centre du polygone
    int cx = 0;
    int cy = 0;
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        cx += this->getTabPoint()->getPoint(i)->getAbs();
        cy += this->getTabPoint()->getPoint(i)->getOrd();
    }
    cx = cx / this->getTabPoint()->getTailleTab();
    cy = cy / this->getTabPoint()->getTailleTab();
    // Mise à jour de l'angle de rotation
    this->rotationAngle += angle;
    // Mise à jour du centre de rotation
    this->rotationCenter.setAbs(cx);
    this->rotationCenter.setOrd(cy);
}
// Scaling 
void Polygon::scaling(const double scaleFactor){
    Logger::log("Scaling du polygon de nom : " + name + " de taille : " + to_string(this->getTabPoint()->getTailleTab()) + " de " + to_string(this->getTabPoint()->getTailleTab()) + " à " + to_string(this->getTabPoint()->getTailleTab()*scaleFactor) + ".");
    // Calculer le centre du polygone
    int cx = 0;
    int cy = 0;
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        cx += this->getTabPoint()->getPoint(i)->getAbs();
        cy += this->getTabPoint()->getPoint(i)->getOrd();
    }
    cx = cx / this->getTabPoint()->getTailleTab();
    cy = cy / this->getTabPoint()->getTailleTab();
    // Mise à jour des coordonnées des points
    for(int i = 0; i < this->getTabPoint()->getTailleTab(); i++){
        this->getTabPoint()->getPoint(i)->setAbs(static_cast<int>((this->getTabPoint()->getPoint(i)->getAbs() - cx) * scaleFactor + cx));
        this->getTabPoint()->getPoint(i)->setOrd(static_cast<int>((this->getTabPoint()->getPoint(i)->getOrd() - cy) * scaleFactor + cy));
    }
    // Mise à jour du centre de rotation
    this->rotationCenter.setAbs(cx);
    this->rotationCenter.setOrd(cy);
}
// Remplissage
void Polygon::fill(const Color color){
    Logger::log("Changement de la couleur de fond du polygon de nom : " + name + " de couleur : " + colorFond.RGBAtoString() + " à " + color.RGBAtoString() + ".");
    this->colorFond = color;
}
// Contour
void Polygon::contour(const Color color){
    Logger::log("Changement de la couleur de contour du polygon de nom : " + name + " de couleur : " + colorBorder.RGBAtoString() + " à " + color.RGBAtoString() + ".");
    this->colorBorder = color;
}