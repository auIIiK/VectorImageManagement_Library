#include "../include/Disc.h"

#include <iostream>
#include <string>

using namespace std;

/* Constructeur */
//Cosntructeur par défault 
Disc::Disc(){
    Logger::log("Constructeur par défaut du Disc.");
    this->type = ShapeType::Ellipsis;
    this->selected = false;
    this->point = Point(0,0);
    this->colorFond = Color(0,0,0);
    this->colorContour = Color(255,255,255);
    this->rayon = 5;
}
//Constructeur par initialisation
Disc::Disc(Point point, Color colorFond, Color colorContour, double rayon){
    Logger::log("Constructeur de Disc de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayon : " + to_string(rayon) + ".");
    this->type = ShapeType::Ellipsis;
    this->selected = false;
    this->point = point;
    this->colorContour = colorContour;
    this->colorFond = colorFond;
    this->rayon = rayon;
}
//Constructeur par copie
Disc::Disc(const Disc &d){
    Logger::log("Constructeur par copie de Disc de nom : " + d.name + ", de centre : (" + to_string(d.point.getAbs()) + "," + to_string(d.point.getOrd()) + "), de couleur de fond : (" + d.colorFond.RGBAtoString() + "), de couleur de contour : (" + d.colorContour.RGBAtoString() + "), de rayon : " + to_string(d.rayon) + ".");
    this->name = d.name;
    this->type = ShapeType::Ellipsis;
    this->selected = d.selected;
    this->point = d.point;
    this->colorContour = d.colorContour;
    this->colorFond = d.colorFond;
    this->rayon = d.rayon;
}

/* Opérateur d'assignation */
Disc& Disc::operator=(const Disc &d){
    if(this != &d){
        this->name = d.name;
        this->type = ShapeType::Ellipsis;
        this->selected = d.selected;
        this->point = d.point;
        this->colorContour = d.colorContour;
        this->colorFond = d.colorFond;
        this->rayon = d.rayon;
        Logger::log("Opérateur d'assignation du Disc de nom : " + d.name + ", de centre : (" + to_string(d.point.getAbs()) + "," + to_string(d.point.getOrd()) + "), de couleur de fond : (" + d.colorFond.RGBAtoString() + "), de couleur de contour : (" + d.colorContour.RGBAtoString() + "), de rayon : " + to_string(d.rayon) + ".");
    }else{
        Logger::log("Opérateur d'assignation du Disc sur lui même de nom : " + d.name + ", de centre : (" + to_string(d.point.getAbs()) + "," + to_string(d.point.getOrd()) + "), de couleur de fond : (" + d.colorFond.RGBAtoString() + "), de couleur de contour : (" + d.colorContour.RGBAtoString() + "), de rayon : " + to_string(d.rayon) + ".");
    }
    return *this;
}

/* Destructeur */
Disc::~Disc(){
    Logger::log("Destructeur de Disc de nom : " + name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayon : " + to_string(rayon) + ".");
}

/* Méthodes */
//getters
Point Disc::getPoint(){
    return this->point;
}
Color Disc::getColorFond(){
    return this->colorFond;
}
Color Disc::getColorContour(){
    return this->colorContour;
}
double Disc::getRayon(){
    return this->rayon;
}
//Aire du disc
double Disc::aire(){
    return 3.14*rayon*rayon;
}
//Information du disc
void Disc::info(){
    cout << " Caractéristique du disque." << endl;
    cout << " Nom : " << name << endl;
    cout << " Point : " << point.getAbs() << " " << point.getOrd() << endl;
    cout << " CouleurContour : " << colorContour.RGBAtoString() << endl;
    cout << " CouleurFond : " << colorFond.RGBAtoString() << endl;
    cout << " Rayon : " << getRayon() << endl;
    cout << " Aire : " << aire() << endl;
}
//Type du disc
Geom2D::ShapeType Disc::getType(){
    return this->type;
}
//Clone l'objet
std::unique_ptr<Geom2D> Disc::clone() const{
    return std::make_unique<Disc>(*this);
}
//Vérifie si le disc est en dehors du canva
bool Disc::isOutside(double width, double height){
    if(point.getAbs() + rayon > width || point.getAbs() - rayon < 0 || point.getOrd() + rayon > height || point.getOrd() - rayon < 0){
        return true;
    }
    return false;
}
//Vérifie si un point est dans le disc
bool Disc::isInside(Point point){
    if((point.getAbs()-this->point.getAbs())*(point.getAbs()-this->point.getAbs()) + (point.getOrd()-this->point.getOrd())*(point.getOrd()-this->point.getOrd()) <= rayon*rayon){
        return true;
    }
    return false;
}
//Surcharge de l'opérateur <<
SVGstream& operator<<(SVGstream &os, Disc &d){
    os << "\n<circle cx=\"" << d.getPoint().getAbs() << "\" cy=\"" << d.getPoint().getOrd() << "\" r=\"" << (float)(d.getRayon()) << "\" fill=\"RGBA(" << d.getColorFond().RGBAtoString() << ")\" stroke=\"RGBA(" << d.getColorContour().RGBAtoString() << ")\" />";
    return os;
}
//print
void Disc::print(SVGstream& os){
    Logger::log("Print du disc.");
    os << *this;
}
//printTikZ
void Disc::printTikZ(TikZstream& os){
    Logger::log("PrintTikZ du disc.");
    os << "\n\\draw[fill={rgb:red," << this->colorFond.getRed()
       << ";green," << this->colorFond.getGreen()
       << ";blue," << this->colorFond.getBlue()
       << "}, opacity=" << this->colorFond.getAlpha() 
       << "] (" << this->point.getAbs() << "," << this->point.getOrd() 
       << ") circle (" << (float)(this->rayon) << ");\n";
}



/* Méthodes virtuel pure */
// Translation
void Disc::translation(const int x, const int y){
    Logger::log("Translation du disc de nom : " + name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayon : " + to_string(rayon) + ".");
    this->point.setAbs(this->point.getAbs()+x);
    this->point.setOrd(this->point.getOrd()+y);
}
// Rotation
void Disc::rotation(const int /* angle */){
    // n'existe pas de rotation pour un disc
}
// Scaling
void Disc::scaling(const double scaleFactor){
    Logger::log("Scaling du disc de nom : " + name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayon : " + to_string(rayon) + ".");
    rayon = rayon*scaleFactor;
}
// Remplissage
void Disc::fill(const Color color){
    Logger::log("Changement de la couleur de fond du disc de nom : " + name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayon : " + to_string(rayon) + ".");
    this->colorFond = color;
}
// Contour
void Disc::contour(const Color color){
    Logger::log("Changement de la couleur de contour du disc de nom : " + name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayon : " + to_string(rayon) + ".");
    this->colorContour = color;
}
