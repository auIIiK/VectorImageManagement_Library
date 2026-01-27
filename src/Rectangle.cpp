#include "../include/Rectangle.h"
#include "../include/Geom2D.h"

#include <iostream>
#include <cmath>

using namespace std;

/* Constructeurs */
//Constructeur par défaut
Rectangle::Rectangle(){
    this->type = ShapeType::Rectangle;
    this->selected = false;
    this->point = Point(1, 2);
    this->hauteur = 3;
    this->largeur = 4;
    this->colorFond = Color(0, 0, 0);
    this->colorContour = Color(255, 255, 255);
    //Calcul du centre de rotation
    this->rotationCenter = Point(this->point.getAbs() + int(this->largeur / 2), this->point.getOrd() + int(this->hauteur / 2));

    Logger::log("Constructeur par défaut du Rectangle.");
}
//Constructeur par initialisation
Rectangle::Rectangle(Point point, float hauteur, float largeur, Color colorFond, Color colorContour){
    this->type = ShapeType::Rectangle;
    this->selected = false;
    this->point = point;
    this->hauteur = hauteur;
    this->largeur = largeur;
    this->colorFond = colorFond;
    this->colorContour = colorContour;
    this->RotationAngle = 0;
    //Calcul du centre de rotation
    this->rotationCenter = Point(this->point.getAbs() + int(this->largeur / 2), this->point.getOrd() + int(this->hauteur / 2));

    Logger::log("Constructeur de Rectangle de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de hauteur : " + to_string(hauteur) + ", de largeur : " + to_string(largeur) + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + ").");
}
//Constructeur par copie
Rectangle::Rectangle(const Rectangle &r){
    this->name = r.name;
    this->type = ShapeType::Rectangle;
    this->selected = r.selected;
    this->point = r.point;
    this->hauteur = r.hauteur;
    this->largeur = r.largeur;
    this->colorFond = r.colorFond;
    this->colorContour = r.colorContour;
    this->RotationAngle = r.RotationAngle;
    //Calcul du centre de rotation
    this->rotationCenter = Point(this->point.getAbs() + int(this->largeur / 2), this->point.getOrd() + int(this->hauteur / 2));

    Logger::log("Constructeur par copie du Rectangle du nom : " + r.name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de hauteur : " + to_string(hauteur) + ", de largeur : " + to_string(largeur) + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + ").");
}

/* Opérateur d'assignation */
Rectangle& Rectangle::operator=(const Rectangle &r){
    if(this != &r){
        this->name = r.name;
        this->type = ShapeType::Rectangle;
        this->selected = r.selected;
        this->point = r.point;
        this->hauteur = r.hauteur;
        this->largeur = r.largeur;
        this->colorFond = r.colorFond;
        this->colorContour = r.colorContour;
        this->RotationAngle = r.RotationAngle;
        //Calcul du centre de rotation
        this->rotationCenter = Point(this->point.getAbs() + int(this->largeur / 2), this->point.getOrd() + int(this->hauteur / 2));

        Logger::log("Opérateur d'assignation du Rectangle du nom : " + r.name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de hauteur : " + to_string(hauteur) + ", de largeur : " + to_string(largeur) + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + ").");
    }else{
        Logger::log("Opérateur d'assignation du Rectangle sur lui-même du nom : " + r.name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de hauteur : " + to_string(hauteur) + ", de largeur : " + to_string(largeur) + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + ").");
    }
    return *this;
}

/* Destructeur */
Rectangle::~Rectangle(){
    Logger::log("Destructeur du Rectangle du nom : " + this->name + ", de centre : (" + to_string(point.getAbs()) + "," + to_string(point.getOrd()) + "), de hauteur : " + to_string(hauteur) + ", de largeur : " + to_string(largeur) + ", de couleur de fond : (" + colorFond.RGBAtoString() + "), de couleur de contour : (" + colorContour.RGBAtoString() + ").");
}

/* Méthodes */
//Getter
Point Rectangle::getPoint(){
    return this->point;
}
float Rectangle::getHauteur(){
    return this->hauteur;
}
float Rectangle::getLargeur(){
    return this->largeur;
}
Color Rectangle::getColorFond(){
    return this->colorFond;
}
Color Rectangle::getColorContour(){
    return this->colorContour;
}
//Aire du rectangle
double Rectangle::aire(){
    return this->hauteur * this->largeur;
}
//Information du rectangle
void Rectangle::info(){
    cout << "Point : (" << this->point.getAbs() << ";" << this->point.getOrd() << ")" << endl;
    cout << "Nom : " << this->name << endl;
    cout << "Hauteur : " << this->hauteur << endl;
    cout << "Largeur : " << this->largeur << endl;
    cout << "Couleur de fond : " << this->colorFond.RGBAtoString() << endl;
    cout << "Couleur de contour : " << this->colorContour.RGBAtoString() << endl;
    cout << "Aire : " << this->aire() << endl;
    //selected value
    cout << "Selected : " << this->selected << endl;
}
//Getter du type
Geom2D::ShapeType Rectangle::getType(){
    return this->type;
}
//Clone l'objet
std::unique_ptr<Geom2D> Rectangle::clone() const{
    return std::make_unique<Rectangle>(*this);
}
//Vérifie si le rectangle est en dehors du canva
bool Rectangle::isOutside(double width, double height){
    if(this->point.getAbs() < 0 || this->point.getAbs() + this->largeur > width || this->point.getOrd() < 0 || this->point.getOrd() + this->hauteur > height){
        return true;
    }
    return false;
}
//Vérifie si un point est dans le rectangle
bool Rectangle::isInside(Point point){
    if(point.getAbs() > this->point.getAbs() && point.getAbs() < this->point.getAbs() + this->largeur && point.getOrd() > this->point.getOrd() && point.getOrd() < this->point.getOrd() + this->hauteur){
        return true;
    }
    return false;
}
//Surcharge de l'opérateur <<
SVGstream& operator<<(SVGstream &os, Rectangle &r){
    //Avec angle de rotation
    os << "\n<rect x=\"" << r.point.getAbs() << "\" y=\"" << r.point.getOrd() << "\" width=\"" << r.largeur << "\" height=\"" << r.hauteur << "\" fill=\"rgba(" << r.colorFond.RGBAtoString() << ")\" stroke=\"rgba(" << r.colorContour.RGBAtoString() << ")\" transform=\"rotate(" << r.RotationAngle << " " << r.rotationCenter.getAbs() << " " << r.rotationCenter.getOrd() << ")\" />";
    return os;
}
//print
void Rectangle::print(SVGstream& os){
    Logger::log("Print du rectangle.");
    os << *this;
}
//printTikZ
void Rectangle::printTikZ(TikZstream& os){
    Logger::log("PrintTikZ du rectangle.");
    os  << "\n\\draw[fill={rgb:red," << this->colorFond.getRed()
        << ";green," << this->colorFond.getGreen()
        << ";blue," << this->colorFond.getBlue()
        << "}, opacity=" << this->colorFond.getAlpha() 
        << "] (" << this->point.getAbs() << "," << this->point.getOrd() 
        << ") rectangle (" << (this->point.getAbs() + this->largeur) 
        << "," << (this->point.getOrd() + this->hauteur) << ");\n";
}

/* Méthodes virtuel pure */
// Translation
void Rectangle::translation(const int x, const int y){
    Logger::log("Translation du Rectangle de (" + to_string(this->point.getAbs()) + "," + to_string(this->point.getOrd()) + ") à (" + to_string(this->point.getAbs() + x) + "," + to_string(this->point.getOrd() + y) + ").");
    this->point.setAbs(this->point.getAbs() + x);
    this->point.setOrd(this->point.getOrd() + y);
    //Calcul du centre de rotation
    this->rotationCenter = Point(this->point.getAbs() + int(this->largeur / 2), this->point.getOrd() + int(this->hauteur / 2));
}
// Rotation
void Rectangle::rotation(const int angle){
    Logger::log("Rotation du Rectangle de " + to_string(this->RotationAngle) + "° à " + to_string(this->RotationAngle + angle) + "°.");
    this->RotationAngle += angle;
    //Calcul du centre de rotation
    this->rotationCenter = Point(this->point.getAbs() + int(this->largeur / 2), this->point.getOrd() + int(this->hauteur / 2));
}
// Scaling
void Rectangle::scaling(const double scaleFactor){
    Logger::log("Scaling du Rectangle de hauteur : " + to_string(this->hauteur) + " à " + to_string(this->hauteur * scaleFactor) + " et de largeur : " + to_string(this->largeur) + " à " + to_string(this->largeur * scaleFactor) + ".");
    this->hauteur *= float(scaleFactor);
    this->largeur *= float(scaleFactor);
    //Calcul du centre de rotation
    this->rotationCenter = Point(this->point.getAbs() + (int)(this->largeur / 2), this->point.getOrd() + (int)(this->hauteur / 2));
}
// Remplissage
void Rectangle::fill(const Color color){
    Logger::log("Changement de la couleur de fond du Rectangle de couleur : " + this->colorFond.RGBAtoString() + " à " + color.RGBAtoString() + ".");
    this->colorFond = color;
}
// Contour
void Rectangle::contour(const Color color){
    Logger::log("Changement de la couleur de contour du Rectangle de couleur : " + this->colorContour.RGBAtoString() + " à " + color.RGBAtoString() + ".");
    this->colorContour = color;
}

