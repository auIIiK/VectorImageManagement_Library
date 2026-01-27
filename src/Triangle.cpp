#include "../include/Triangle.h"

#include <iostream>
#include <cmath>


using namespace std;

/* Constructeurs */
//Constructeur par défaut
Triangle::Triangle(){
    this->type = ShapeType::Triangle;
    this->selected = false;
    this->point1 = Point(1, 2);
    this->point2 = Point(3, 4);
    this->point3 = Point(5, 6);
    this->colorFond = Color(0, 0, 0);
    this->colorContour = Color(255, 255, 255);
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);

    Logger::log("Constructeur par défaut du Triangle " );
}
//Constructeur par initialisation
Triangle::Triangle(Point point1, Point point2, Point point3, Color colorFond, Color colorContour){
    this->type = ShapeType::Triangle;
    this->selected = false;
    this->point1 = point1;
    this->point2 = point2;
    this->point3 = point3;
    this->colorFond = colorFond;
    this->colorContour = colorContour;
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);

    Logger::log("Constructeur par initialisation du Triangle de points : (" + to_string(point1.getAbs()) + ";" + to_string(point1.getOrd()) + "), (" + to_string(point2.getAbs()) + ";" + to_string(point2.getOrd()) + "), (" + to_string(point3.getAbs()) + ";" + to_string(point3.getOrd()) + ")");
}
//Constructeur par copie
Triangle::Triangle(const Triangle &t){
    this->name = t.name;
    this->type = ShapeType::Triangle;
    this->selected = t.selected;
    this->point1 = t.point1;
    this->point2 = t.point2;
    this->point3 = t.point3;
    this->colorFond = t.colorFond;
    this->colorContour = t.colorContour;
    //Calcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);

    Logger::log("Constructeur par copie du Triangle du nom : " + t.name + " de points : (" + to_string(t.point1.getAbs()) + ";" + to_string(t.point1.getOrd()) + "), (" + to_string(t.point2.getAbs()) + ";" + to_string(t.point2.getOrd()) + "), (" + to_string(t.point3.getAbs()) + ";" + to_string(t.point3.getOrd()) + ")");
}

/* Opérateur d'assignation */
Triangle& Triangle::operator=(const Triangle &t){
    if(this != &t){
        this->name = t.name;
        this->type = ShapeType::Triangle;
        this->selected = t.selected;
        this->point1 = t.point1;
        this->point2 = t.point2;
        this->point3 = t.point3;
        this->colorFond = t.colorFond;
        this->colorContour = t.colorContour;
        //Calcul du centre de rotation
        this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);

        Logger::log("Opérateur d'assignation du Triangle du nom : " + t.name + " de points : (" + to_string(t.point1.getAbs()) + ";" + to_string(t.point1.getOrd()) + "), (" + to_string(t.point2.getAbs()) + ";" + to_string(t.point2.getOrd()) + "), (" + to_string(t.point3.getAbs()) + ";" + to_string(t.point3.getOrd()) + ")");
    }else{
        Logger::log("Opérateur d'assignation du Triangle sur lui-même.");
    }
    return *this;
}

/* Destructeur */
Triangle::~Triangle(){
    //Pas d'allocation dynamique
    Logger::log("Destructeur du Triangle :" + this->name);
}

/* Méthodes */ 
//Getter
Point Triangle::getPoint1(){
    return this->point1;
}
Point Triangle::getPoint2(){
    return this->point2;
}
Point Triangle::getPoint3(){
    return this->point3;
}
Color Triangle::getColorFond(){
    return this->colorFond;
}
Color Triangle::getColorContour(){
    return this->colorContour;
}
//Aire du triangle
double Triangle::aire(){
    return std::abs((this->point1.getAbs() * (this->point2.getOrd() - this->point3.getOrd()) + this->point2.getAbs() * (this->point3.getOrd() - this->point1.getOrd()) + this->point3.getAbs() * (this->point1.getOrd() - this->point2.getOrd())) / 2);
}
//Information du triangle
void Triangle::info(){
    cout << "Triangle : " << endl;
    cout << "Nom : " << this->name << endl;
    cout << "Point 1 : (" << this->point1.getAbs() << ";" << this->point1.getOrd() << ")" << endl;
    cout << "Point 2 : (" << this->point2.getAbs() << ";" << this->point2.getOrd() << ")" << endl;
    cout << "Point 3 : (" << this->point3.getAbs() << ";" << this->point3.getOrd() << ")" << endl;
    cout << "ColorFond : " << getColorFond().RGBAtoString() << endl;
    cout << "ColorContour : " << getColorContour().RGBAtoString() << endl;
    cout << "Aire : " << aire() << endl;
    cout << "Selected : " << this->selected << endl;
}
//Type du triangle
Triangle::ShapeType Triangle::getType(){
    return this->type;
}
//Clone l'objet
std::unique_ptr<Geom2D> Triangle::clone() const{
    return std::make_unique<Triangle>(*this);
}
//Vérifie si le triangle est en dehors du canva
bool Triangle::isOutside(double width, double height){
    if(this->point1.getAbs() < 0 || this->point1.getAbs() > width || this->point1.getOrd() < 0 || this->point1.getOrd() > height){
        return true;
    }
    if(this->point2.getAbs() < 0 || this->point2.getAbs() > width || this->point2.getOrd() < 0 || this->point2.getOrd() > height){
        return true;
    }
    if(this->point3.getAbs() < 0 || this->point3.getAbs() > width || this->point3.getOrd() < 0 || this->point3.getOrd() > height){
        return true;
    }
    return false;
}
//Vérifie si un point est dans le triangle
bool Triangle::isInside(Point point){
    double A = aire();
    double A1 = std::abs((point.getAbs() * (this->point1.getOrd() - this->point2.getOrd()) + this->point1.getAbs() * (this->point2.getOrd() - point.getOrd()) + this->point2.getAbs() * (point.getOrd() - this->point1.getOrd())) / 2);
    double A2 = std::abs((point.getAbs() * (this->point2.getOrd() - this->point3.getOrd()) + this->point2.getAbs() * (this->point3.getOrd() - point.getOrd()) + this->point3.getAbs() * (point.getOrd() - this->point2.getOrd())) / 2);
    double A3 = std::abs((point.getAbs() * (this->point3.getOrd() - this->point1.getOrd()) + this->point3.getAbs() * (this->point1.getOrd() - point.getOrd()) + this->point1.getAbs() * (point.getOrd() - this->point3.getOrd())) / 2);
    return A == A1 + A2 + A3;
}
//Surchage de l'opérateur <<
SVGstream& operator<<(SVGstream &os, Triangle &t){
    //Avec angle de rotation
    os << "\n<polygon points=\"" << t.getPoint1().getAbs() << "," << t.getPoint1().getOrd() << " " << t.getPoint2().getAbs() << "," << t.getPoint2().getOrd() << " " << t.getPoint3().getAbs() << "," << t.getPoint3().getOrd() << "\" fill=\"rgba(" << t.getColorFond().RGBAtoString() << ")\" stroke=\"rgba(" << t.getColorContour().RGBAtoString() << ")\" transform=\"rotate(" << t.RotationAngle << " " << t.rotationCenter.getAbs() << " " << t.rotationCenter.getOrd() << ")\" />";
    return os;
}
//print
void Triangle::print(SVGstream& os){
    Logger::log("Print du Triangle : " + this->name);
    os << *this;
}
//printTikZ
void Triangle::printTikZ(TikZstream& os){
    Logger::log("PrintTikZ du Triangle : " + this->name);
    os << "\n\\draw[fill={rgb:red," << this->colorFond.getRed()
       << ";green," << this->colorFond.getGreen()
       << ";blue," << this->colorFond.getBlue()
       << "}, opacity=" << this->colorFond.getAlpha()
       << "] (" << this->point1.getAbs() << "," << this->point1.getOrd() 
       << ") -- (" << this->point2.getAbs() << "," << this->point2.getOrd() 
       << ") -- (" << this->point3.getAbs() << "," << this->point3.getOrd() 
       << ") -- cycle;\n";
}

/* Méthodes virtuel pure */
// Translation
void Triangle::translation(const int x, const int y){

    Logger::log("Translation du Triangle : " + this->name);
    //Translation des points par rapport au barycentre
    this->point1.setAbs(this->point1.getAbs() + x);
    this->point1.setOrd(this->point1.getOrd() + y);
    this->point2.setAbs(this->point2.getAbs() + x);
    this->point2.setOrd(this->point2.getOrd() + y);
    this->point3.setAbs(this->point3.getAbs() + x);
    this->point3.setOrd(this->point3.getOrd() + y);
    //recalcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);
    

}
// Rotation
void Triangle::rotation(const int angle){
    Logger::log("Rotation du Triangle : " + this->name);
    //Rotate par rapport au barycentre
    double angleRad = angle * M_PI / 180;
    double x1 = this->point1.getAbs() - this->rotationCenter.getAbs();
    double y1 = this->point1.getOrd() - this->rotationCenter.getOrd();
    double x2 = this->point2.getAbs() - this->rotationCenter.getAbs();
    double y2 = this->point2.getOrd() - this->rotationCenter.getOrd();
    double x3 = this->point3.getAbs() - this->rotationCenter.getAbs();
    double y3 = this->point3.getOrd() - this->rotationCenter.getOrd();
    this->point1.setAbs(this->rotationCenter.getAbs() + (int)(x1 * cos(angleRad) - y1 * sin(angleRad)));
    this->point1.setOrd(this->rotationCenter.getOrd() + (int)(x1 * sin(angleRad) + y1 * cos(angleRad)));
    this->point2.setAbs(this->rotationCenter.getAbs() + (int)(x2 * cos(angleRad) - y2 * sin(angleRad)));
    this->point2.setOrd(this->rotationCenter.getOrd() + (int)(x2 * sin(angleRad) + y2 * cos(angleRad)));
    this->point3.setAbs(this->rotationCenter.getAbs() + (int)(x3 * cos(angleRad) - y3 * sin(angleRad)));
    this->point3.setOrd(this->rotationCenter.getOrd() + (int)(x3 * sin(angleRad) + y3 * cos(angleRad)));
    this->RotationAngle += angle;
    //recalcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);

    

}
// Scaling
void Triangle::scaling(const double scaleFactor){
    Logger::log("Scaling du Triangle : " + this->name);
    //Scale
    this->point1.setAbs(this->rotationCenter.getAbs() + int(scaleFactor) * (this->point1.getAbs() - this->rotationCenter.getAbs()));
    this->point1.setOrd(this->rotationCenter.getOrd() + int(scaleFactor) * (this->point1.getOrd() - this->rotationCenter.getOrd()));
    this->point2.setAbs(this->rotationCenter.getAbs() + int(scaleFactor) * (this->point2.getAbs() - this->rotationCenter.getAbs()));
    this->point2.setOrd(this->rotationCenter.getOrd() + int(scaleFactor) * (this->point2.getOrd() - this->rotationCenter.getOrd()));
    this->point3.setAbs(this->rotationCenter.getAbs() + int(scaleFactor) * (this->point3.getAbs() - this->rotationCenter.getAbs()));
    this->point3.setOrd(this->rotationCenter.getOrd() + int(scaleFactor) * (this->point3.getOrd() - this->rotationCenter.getOrd()));
    //recalcul du centre de rotation
    this->rotationCenter = Point((this->point1.getAbs() + this->point2.getAbs() + this->point3.getAbs()) / 3, (this->point1.getOrd() + this->point2.getOrd() + this->point3.getOrd()) / 3);
}
// Remplissage
void Triangle::fill(const Color color){
    Logger::log("Remplissage du Triangle : " + this->name);
    this->colorFond = color;
}
// Contour
void Triangle::contour(const Color color){
    Logger::log("Contour du Triangle : " + this->name); 
    this->colorContour = color;
}




