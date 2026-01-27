#include "../include/Ellipse.h"

#include <iostream>
#include <string>

using namespace std;

/* Constructeurs */
//Constructeur par défaut
Ellipse::Ellipse(){
    this->type = ShapeType::Ellipsis;
    this->selected = false;
    this->rayonX = 100;
    this->rayonY = 50;
    this->point = Point(0,0);
    this->colorContour = Color(255,255,255,1);
    this->colorFond = Color(0,0,0,1);

    Logger::log("Constructeur par défaut de l'ellipse.");
}
//Constructeur par initialisation
Ellipse::Ellipse(Point point, Color colorFond, Color colorContour, double rayonX, double rayonY){
    this->type = ShapeType::Ellipsis;
    this->selected = false;
    this->point = point;
    this->colorFond = colorFond;
    this->colorContour = colorContour;
    this->rayonX = rayonX;
    this->rayonY = rayonY;

    Logger::log("Constructeur de l'ellipse de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayonX : " + to_string(rayonX) + ", de rayonY : " + to_string(rayonY) + ".");
}
//Constructeur par copie
Ellipse::Ellipse(const Ellipse &e){
    this->type = e.type;
    this->selected = e.selected;
    this->name = e.name;
    this->RotationAngle = e.RotationAngle;
    this->point = e.point;
    this->colorFond = e.colorFond;
    this->colorContour = e.colorContour;
    this->rayonX = e.rayonX;
    this->rayonY = e.rayonY;

    Logger::log("Constructeur par copie de l'ellipse du nom : " + e.name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayonX : " + to_string(rayonX) + ", de rayonY : " + to_string(rayonY) + ".");
}

/* Opérateur d'assignation */
Ellipse& Ellipse::operator=(const Ellipse &e){
    if(this != &e){
        this->type = e.type;
        this->selected = e.selected;
        this->name = e.name;
        this->RotationAngle = e.RotationAngle;
        this->point = e.point;
        this->colorFond = e.colorFond;
        this->colorContour = e.colorContour;
        this->rayonX = e.rayonX;
        this->rayonY = e.rayonY;
        Logger::log("Opérateur d'assignation de l'ellipse du nom : " + e.name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayonX : " + to_string(rayonX) + ", de rayonY : " + to_string(rayonY) + ".");
    }else{
        Logger::log("Opérateur d'assignation de l'ellipse sur elle-même du nom : " + e.name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayonX : " + to_string(rayonX) + ", de rayonY : " + to_string(rayonY) + ".");
    }
    return *this;
}

/* Destructeur */
Ellipse::~Ellipse(){
    Logger::log("Destructeur de l'ellipse du nom : " + name + " de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + "), de rayonX : " + to_string(rayonX) + ", de rayonY : " + to_string(rayonY) + ".");
}

/* Méthodes */
//Getter
Point Ellipse::getPoint(){
    return this->point;
}
Color Ellipse::getColorFond(){
    return this->colorFond;
}
Color Ellipse::getColorContour(){
    return this->colorContour;
}
double Ellipse::getRayonX(){
    return this->rayonX;
}
double Ellipse::getRayonY(){
    return this->rayonY;
}
//Aire de l'ellispe
double Ellipse::aire(){
    return rayonX * rayonY * 3.14;
}
//Information de l'ellipse
void Ellipse::info(){
    cout << " Caractéristique du disque." << endl;
    cout << " Nom : " << name << endl;
    cout << " Point : " << point.getAbs() << " " << point.getOrd() << endl;
    cout << " CouleurContour : " << colorContour.RGBAtoString() << endl;
    cout << " CouleurFond : " << colorFond.RGBAtoString() << endl;
    cout << " RayonX : " << getRayonX() << endl;
    cout << " RayonY : " << getRayonY() << endl;
    cout << " Aire : " << aire() << endl;
}
//Type de l'ellipse
Ellipse::ShapeType Ellipse::getType(){
    return ShapeType::Ellipsis;
}
//Clone l'objet
std::unique_ptr<Geom2D> Ellipse::clone() const{
    return std::make_unique<Ellipse>(*this);
}
//Vérifie si l'ellipse est en dehors du canva
bool Ellipse::isOutside(double width, double height){
    if(point.getAbs() + rayonX > width || point.getAbs() - rayonX < 0 || point.getOrd() + rayonY > height || point.getOrd() - rayonY < 0){
        return true;
    }
    return false;
}
//Vérifie si un point est dans l'ellipse
bool Ellipse::isInside(Point point){
    if(((point.getAbs() - this->point.getAbs())*(point.getAbs() - this->point.getAbs()))/(rayonX*rayonX) + ((point.getOrd() - this->point.getOrd())*(point.getOrd() - this->point.getOrd()))/(rayonY*rayonY) <= 1){
        return true;
    }
    return false;
}
//Surcharge de l'opérateur <<
SVGstream& operator<<(SVGstream &os, const Ellipse &e){
    //Avec angle de rotation
    if(e.RotationAngle != 0){
        os << "\n<ellipse cx=\"" << e.point.getAbs() << "\" cy=\"" << e.point.getOrd() << "\" rx=\"" << float(e.rayonX) << "\" ry=\"" << float(e.rayonY) << "\" fill=\"rgba(" << e.colorFond.RGBAtoString() << ")\" stroke=\"rgba(" << e.colorContour.RGBAtoString() << ")\" transform=\"rotate(" << e.RotationAngle << " " << e.point.getAbs() << " " << e.point.getOrd() << ")\" />";
    }else{
        os << "\n<ellipse cx=\"" << e.point.getAbs() << "\" cy=\"" << e.point.getOrd() << "\" rx=\"" << float(e.rayonX) << "\" ry=\"" << float(e.rayonY) << "\" fill=\"rgba(" << e.colorFond.RGBAtoString() << ")\" stroke=\"rgba(" << e.colorContour.RGBAtoString() << ")\" />";
    }
    return os;
}
//print
void Ellipse::print(SVGstream& os){
    Logger::log("Print de l'ellipse.");
    os << *this;
}
//printTikZ
void Ellipse::printTikZ(TikZstream& os){
    Logger::log("PrintTikZ de l'ellipse.");
    os << "\n\\draw[fill={rgb:red," << this->colorFond.getRed()
       << ";green," << this->colorFond.getGreen()
       << ";blue," << this->colorFond.getBlue()
       << "}, opacity=" << this->colorFond.getAlpha() 
       << "] (" << this->point.getAbs() << "," << this->point.getOrd() 
       << ") ellipse [" << "x radius=" << float(this->rayonX) 
       << ", y radius=" << float(this->rayonY) << "];\n";
}


/* Méthodes virtuel pure */
// Translation
void Ellipse::translation(const int x, const int y){
    Logger::log("Translation de l'ellipse du nom : " + name + " de (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + ") à (" + to_string(point.getAbs()+x) + "," + to_string(point.getOrd()+y) + ").");
    this->point.setAbs(this->point.getAbs()+x);
    this->point.setOrd(this->point.getOrd()+y);
}
// Rotation
void Ellipse::rotation(const int angle){
    Logger::log("Rotation de l'ellipse du nom : " + name + " de " + to_string(RotationAngle) + "° à " + to_string(RotationAngle+angle) + "°.");
    this->RotationAngle += angle;
}
// Scaling
void Ellipse::scaling(const double scaleFactor){
    Logger::log("Scaling de l'ellipse du nom : " + name + " de rayonX : " + to_string(rayonX) + " à " + to_string(rayonX*scaleFactor) + " et de rayonY : " + to_string(rayonY) + " à " + to_string(rayonY*scaleFactor) + ".");
    this->rayonX = rayonX * scaleFactor;
    this->rayonY = rayonY * scaleFactor;
}
// Remplissage
void Ellipse::fill(const Color color){
    Logger::log("Changement de la couleur de fond de l'ellipse du nom : " + name + " de couleur : " + colorFond.RGBAtoString() + " à " + color.RGBAtoString() + ".");
    this->colorFond = color;
}
// Contour
void Ellipse::contour(const Color color){
    Logger::log("Changement de la couleur de contour de l'ellipse du nom : " + name + " de couleur : " + colorContour.RGBAtoString() + " à " + color.RGBAtoString() + ".");
    this->colorContour = color;
}