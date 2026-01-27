#include "../include/Stroke.h"

#include <iostream>
#include <string>

using namespace std;

/* Constructeur */
//Cosntructeur par défault
Stroke::Stroke(){
    Logger::log("Constructeur par défaut du Stroke.");
    this->type = ShapeType::Stroke;
    this->selected = false;
    this->point1 = Point(0,0);
    this->point2 = Point(0,0);
    this->color = Color(255,255,255);
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);
}
//Constructeur par initialisation
Stroke::Stroke(Point point1, Point point2, Color colorContour){
    Logger::log("Constructeur de Stroke de point 1 : (" + to_string(point1.getAbs()) + "," + to_string(point1.getOrd()) + "), de point 2 : (" + to_string(point2.getAbs()) + "," + to_string(point2.getOrd()) + "), de couleur de contour : (" + colorContour.RGBAtoString() + ").");
    this->type = ShapeType::Stroke;
    this->selected = false;
    this->point1 = point1;
    this->point2 = point2;
    this->color = colorContour;
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);
}
//Constructeur par copie
Stroke::Stroke(const Stroke &s){
    Logger::log("Constructeur par copie de Stroke de nom : " + s.name + ", de point 1 : (" + to_string(s.point1.getAbs()) + "," + to_string(s.point1.getOrd()) + "), de point 2 : (" + to_string(s.point2.getAbs()) + "," + to_string(s.point2.getOrd()) + "), de couleur de contour : (" + s.color.RGBAtoString() + ").");
    this->name = s.name;
    this->type = ShapeType::Stroke;
    this->selected = s.selected;
    this->point1 = s.point1;
    this->point2 = s.point2;
    this->color = s.color;
    this->RotationAngle = s.RotationAngle;
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);
}

/* Opérateur d'assignation */
Stroke& Stroke::operator=(const Stroke &s){
    if(this != &s){
        this->name = s.name;
        this->type = ShapeType::Stroke;
        this->selected = s.selected;
        this->point1 = s.point1;
        this->point2 = s.point2;
        this->color = s.color;
        this->RotationAngle = s.RotationAngle;
        //Calcul du centre de rotation
        this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);
        Logger::log("Opérateur d'assignation du Stroke de nom : " + s.name + ", de point 1 : (" + to_string(s.point1.getAbs()) + "," + to_string(s.point1.getOrd()) + "), de point 2 : (" + to_string(s.point2.getAbs()) + "," + to_string(s.point2.getOrd()) + "), de couleur de contour : (" + s.color.RGBAtoString() + ").");
    }else{
        Logger::log("Opérateur d'assignation du Stroke sur lui même de nom : " + s.name + ", de point 1 : (" + to_string(s.point1.getAbs()) + "," + to_string(s.point1.getOrd()) + "), de point 2 : (" + to_string(s.point2.getAbs()) + "," + to_string(s.point2.getOrd()) + "), de couleur de contour : (" + s.color.RGBAtoString() + ").");
    }
    return *this;
}

/* Destructeur */
Stroke::~Stroke(){
    Logger::log("Destructeur de Stroke de nom : " + name + ", de point 1 : (" + to_string(point1.getAbs()) + "," + to_string(point1.getOrd()) + "), de point 2 : (" + to_string(point2.getAbs()) + "," + to_string(point2.getOrd()) + "), de couleur de contour : (" + color.RGBAtoString() + ").");
}

/* Méthodes */
//Getter
Point Stroke::getPoint1(){
    return this->point1;
}
Point Stroke::getPoint2(){
    return this->point2;
}
Color Stroke::getColorContour(){
    return this->color;
}
Color Stroke::getColorFond(){
    return this->color;
}
//Longueur du trait
double Stroke::longueur(){
    return point1.distance(point2);
}
//Information du trait
void Stroke::info(){
    cout << "Information du trait : " << endl;
    cout << "Nom : " << this->name << endl;
    cout << "Point 1 : (" << point1.getAbs() << "," << point1.getOrd() << "), Point 2 : (" << point2.getAbs() << "," << point2.getOrd() << "), Longueur : " << longueur() << "." << endl;
    cout << "Couleur : " << this->color.RGBAtoString() << endl;
    //selected value
    cout << "Selected : " << this->selected << endl;
}
//Aire du trait
double Stroke::aire(){
    return 0;
}
//Type du trait
Geom2D::ShapeType Stroke::getType(){
    return this->type;
}
//Clone l'objet
std::unique_ptr<Geom2D> Stroke::clone() const{
    return std::make_unique<Stroke>(*this);
}
//Vérifie si le trait est en dehors du canva
bool Stroke::isOutside(double width, double height){
    return (point1.getAbs() < 0 || point1.getAbs() > width || point1.getOrd() < 0 || point1.getOrd() > height || point2.getAbs() < 0 || point2.getAbs() > width || point2.getOrd() < 0 || point2.getOrd() > height);
}
//Vérifie si un point est dans le trait
bool Stroke::isInside(Point point){
    return (point1.distance(point) + point2.distance(point) == longueur());
}
//Surcharge de l'opérateur <<
SVGstream& operator<<(SVGstream &os, Stroke &s){
    //avec angle de rotation
    os << "\n<line x1=\"" << s.point1.getAbs() << "\" y1=\"" << s.point1.getOrd() << "\" x2=\"" << s.point2.getAbs() << "\" y2=\"" << s.point2.getOrd() << "\" stroke=\"rgba(" << s.color.RGBAtoString() << ")\" transform=\"rotate(" << s.RotationAngle << " " << s.rotationCenter.getAbs() << " " << s.rotationCenter.getOrd() << ")\" />";
    return os;
}
//print
void Stroke::print(SVGstream& os){
    os << *this;
}
//printTikZ
void Stroke::printTikZ(TikZstream& os){
    os << "\\draw[draw=" << color.RGBAtoString() 
       << "] (" << point1.getAbs() 
       << "," << point1.getOrd() 
       << ") -- (" << point2.getAbs() 
       << "," << point2.getOrd() << ");\n";
}

/* Méthodes virtuel pure */
// Translation
void Stroke::translation(const int x, const int y){
    this->point1.setAbs(this->point1.getAbs() + x);
    this->point1.setOrd(this->point1.getOrd() + y);
    this->point2.setAbs(this->point2.getAbs() + x);
    this->point2.setOrd(this->point2.getOrd() + y);
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);
}
// Rotation
void Stroke::rotation(const int angle){
    this->RotationAngle += angle;
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);
}
// Scaling
void Stroke::scaling(const double scaleFactor){
    // Calcul du centre de rotation
    Point center((this->point1.getAbs() + this->point2.getAbs()) / 2, (this->point1.getOrd() + this->point2.getOrd()) / 2);

    // Calcul des nouvelles coordonnées des points
    this->point1.setAbs(center.getAbs() + (int)((this->point1.getAbs() - center.getAbs()) * scaleFactor));
    this->point1.setOrd(center.getOrd() + (int)((this->point1.getOrd() - center.getOrd()) * scaleFactor));
    this->point2.setAbs(center.getAbs() + (int)((this->point2.getAbs() - center.getAbs()) * scaleFactor));
    this->point2.setOrd(center.getOrd() + (int)((this->point2.getOrd() - center.getOrd()) * scaleFactor));

    // Mise à jour du centre de rotation
    this->rotationCenter = center;
}
// Remplissage
void Stroke::fill(const Color /* color */){
    // n'existe pas de remplissage pour un trait
}
// Contour
void Stroke::contour(const Color color){
    this->color = color;
}