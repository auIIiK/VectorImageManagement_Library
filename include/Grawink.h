#ifndef _GRAWINK_H_
#define _GRAWINK_H_

#include "Geom2D.h"
#include "Point.h"
#include "Color.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"
#include "Disc.h"
#include "Ellipse.h"
#include "Text.h"
#include "Polygon.h"
#include "Logger.h"
#include "Stroke.h"

#include <map>
#include <regex>
#include <cstdint>
#include <vector>
#include <iostream>
#include <sstream>


using namespace std;

struct Action
{
  // Type de l'action
  enum class ActionType
  {
    Add,
    Delete,
    Rotate,
    Translate,
    Scale,
    fill,
    contour,
    other,
    crop
  };
  // Figure
  std::unique_ptr<Geom2D> shape;

  //nom de la figure
  string name;

  // Type de l'action
  ActionType ActionType;

  // Taille Canva
  double width = 0;
  double height = 0;

};


class GrawEditor {
  public:

    using ShapeType = Geom2D::ShapeType;

  private:
    /* Tableau de figure */
    std::vector<std::unique_ptr<Geom2D>> canva;

    /* Taille du canva */
    double width;
    double height;
    Color colorFond;

    /* instance unique de mon grawEditor */
    static GrawEditor* instance;

    /* Constructeur privé pour le singleton */
    GrawEditor(double width, double height, Color colorFond);

    /* Liste des undo */
    std::vector<std::unique_ptr<Action>> undoList;

    /* Liste des redo */
    std::vector<std::unique_ptr<Action>> redoList;





  public:

    static GrawEditor& GetEditor(double width, double height, Color colorFond);

    static void DeleteInstance();

    // Crée une nouvelle instance de la classe `Shape` (i.e. Rectangle,
    // Triangle, Stroke, Circle, etc.) et retourne un pointeur vers l'objet nouvellement alloué.
    // Cet objet peut ensuite être transformé, passé en paramètre à `Add` ou à `Delete`.
    template <typename ShapeType, typename... Args>
    ShapeType *GetNew(Args... args) {
        Logger::log("GetNew shape");
        return new ShapeType(args...);
    }

    // Ajoute un nouveau objet au canevas
    template <typename ShapeType, typename... Args>
    GrawEditor& Add(const std::string& name, Args... args) {
      Logger::log("Add shape " + name);
      // Créez une nouvelle forme
      ShapeType* newShape = GetNew<ShapeType>(args...);
      newShape->name = name;



      // Ajoutez la nouvelle forme à canva
      canva.push_back(std::unique_ptr<ShapeType>(newShape));
      // Clone la forme pour l'ajouter à la liste des undo
      undoList.push_back(std::make_unique<Action>(Action{newShape->clone(), name, Action::ActionType::Add}));

      return *this;
    }

    // Méthode qui affiche les forme de undoList et leur type d'action
    void printUndoList(){
      Logger::log("UndoList : ");
      for (const auto& action : undoList) { 
        Logger::log("Name : " + action->name);
        Logger::log("Action : ");
        switch (action->ActionType)
        {
        case Action::ActionType::Add:
          Logger::log("Add");
          break;
        case Action::ActionType::Delete:
          Logger::log("Delete");
          break;
        case Action::ActionType::Rotate:
          Logger::log("Rotate");
          break;
        case Action::ActionType::Translate:
          Logger::log("Translate");
          break;
        case Action::ActionType::Scale:
          Logger::log("Scale");
          break;
        case Action::ActionType::fill:
          Logger::log("fill");
          break;
        case Action::ActionType::contour:
          Logger::log("contour");
          break;
        case Action::ActionType::other:
          Logger::log("other");
          break;
        default:
          break;
        }
      }
    }

    // Méthode qui affiche les forme de redoList et leur type d'action
    void printRedoList(){
      Logger::log("RedoList : ");
      for (const auto& action : redoList) {
        Logger::log("Name : " + action->name);
        Logger::log("Action : ");
        switch (action->ActionType)
        {
        case Action::ActionType::Add:
          Logger::log("Add");
          break;
        case Action::ActionType::Delete:
          Logger::log("Delete");
          break;
        case Action::ActionType::Rotate:
          Logger::log("Rotate");
          break;
        case Action::ActionType::Translate:
          Logger::log("Translate");
          break;
        case Action::ActionType::Scale:
          Logger::log("Scale");
          break;
        case Action::ActionType::fill:
          Logger::log("fill");
          break;
        case Action::ActionType::contour:
          Logger::log("contour");
          break;
        case Action::ActionType::other:
          Logger::log("other");
          break;
        default:
          break;
        }
      }
    }
    

    // Supprime un objet du canevas
    GrawEditor& Delete(const std::string& name);

    // Annule le dernier ajout d'objet // ou la dernière modification d'objet effectuée
    GrawEditor& Undo(int n);

    // Réinsère le dernier objet supprimé // ou la dernière modification annulée
    GrawEditor& Redo(int n);

    // Redimensionne le canevas
    GrawEditor& Resize(double width, double height);

    // Repaint le canevas
    GrawEditor& Repaint(Color colorFond);

    // Redimensionne le canevas en supprimant definitivement les objets extérieurs 
    GrawEditor& Crop(double width, double height);

    // Sélectionne les objets à exporter/afficher.
    // La sélection pourra se faire sous la forme d'une disjonction ("OU" binaires) de `enum ShapeType`.
    // Par exemple pour sélectionner uniquement les triangles, les rectangles et les octogones, on pourra passer en paramètre :
    //  ShapeType::Triangle | ShapeType::Rectangle | ShapeType::Octogon, ou
    //  bien l'équivalent en hexadécimal (0x46ULL), ou en décimal (70ULL).
    // Passer ShapeType::All resélectionne l'ensemble des formes du canevas.
    GrawEditor& Select(ShapeType shapeType);

    // Déselectionne mes objets
    GrawEditor& Deselect(ShapeType shapeType);

    // Affiche l'ensemble des objets contenus dans le canevas, triés par
    // catégorie, dans la sortie standard.
    GrawEditor& Print();

    // Écrit le code SVG résultant des objets contenus dans le canevas
    GrawEditor& ExportSVG(const string& filename, bool PureSvg);

    // Ecrit le code TikZ résultant des objets contenus dans le canevas
    GrawEditor& ExportTikZ(const string& filename);

    // Méthode qui vérifie si un point est dans une forme
    bool IsInShape(const std::string& name, Point point);

    // Ecrit une image sous format PPM (format binaire accepté par tout visualiseur d'image) résultant des objets contenus dans le canevas
    //Sans transparence
    GrawEditor& ExportPPM(const string& filename);
    //Avec transparence
    GrawEditor& ExportPAM(const string& filename);

    // Méthode qui rotate les formes et les ajoute à la liste des undo
    GrawEditor& Rotate(const std::string& name, int angle);

    // Méthode qui translate les formes et les ajoute à la liste des undo
    GrawEditor& Translate(const std::string& name, int x, int y);

    // Méthode qui scale les formes et les ajoute à la liste des undo
    GrawEditor& Scale(const std::string& name, double scaleFactor);

    // Méthode qui fill les formes et les ajoute à la liste des undo
    GrawEditor& Fill(const std::string& name, Color color);

    // Méthode qui contour les formes et les ajoute à la liste des undo
    GrawEditor& Contour(const std::string& name, Color color);

    // Méthode qui ajoute des points à un polygone
    GrawEditor& AddPointPolygon(const std::string& name, Point point);

    // Méthode qui supprime des points à un polygone
    GrawEditor& RemovePointPolygon(const std::string& name, int indexPoint);

    // Méthode qui load un SVG
    GrawEditor& LoadSVG(const string& filename);

};


#endif // _GRAWINK_H_