#include "../include/Text.h"

#include <iostream>
#include <string>

using namespace std;

/* Constructeurs */
//Constructeurs par défault
Text::Text(){
    this->type = ShapeType::Text;
    this->selected = false;
    this->text = "Hello World !";
    this->font = "Arial";
    this->size = 12;
    this->thickness = 1;
    this->colorFond = Color(0,0,0,1);
    this->colorContour = Color(255,255,255,1);
    this->point = Point(0,0);
    //Calcul du point RotationCenter
    this->RotationCenter.setAbs(point.getAbs() + size/2);
    this->RotationCenter.setOrd(point.getOrd() + size/2);

    Logger::log("Constructeur par défaut du Text : " + text);
};
//Constructeur avec paramètres
Text::Text(string t, string f, int s, int th, Color cF, Color cC, Point p){
    this->type = ShapeType::Text;
    this->selected = false;
    this->text = t;
    this->font = f;
    this->size = s;
    this->thickness = th;
    this->colorFond = cF;
    this->colorContour = cC;
    this->point = p;
    //Calcul du point RotationCenter
    this->RotationCenter.setAbs(point.getAbs() + size/2);
    this->RotationCenter.setOrd(point.getOrd() + size/2);

    Logger::log("Constructeur avec paramètres du Text : " + text);
};
//Constructeur par copie
Text::Text(const Text &t){
    this->name = t.name;
    this->type = ShapeType::Text;
    this->selected = t.selected;
    this->text = t.text;
    this->font = t.font;
    this->size = t.size;
    this->thickness = t.thickness;
    this->colorFond = t.colorFond;
    this->colorContour = t.colorContour;
    this->point = t.point;
    //Calcul du point RotationCenter
    this->RotationCenter.setAbs(point.getAbs() + size/2);
    this->RotationCenter.setOrd(point.getOrd() + size/2);

    Logger::log("Constructeur par copie du Text : " + text);
};

/* Destructeur */
Text::~Text(){
    Logger::log("Destructeur du Text : " + text);
};

/* Opérateur d'assignation */
Text& Text::operator=(const Text &t){
    if(this != &t){
        this->name = t.name;
        this->type = ShapeType::Text;
        this->selected = t.selected;
        this->text = t.text;
        this->font = t.font;
        this->size = t.size;
        this->thickness = t.thickness;
        this->colorFond = t.colorFond;
        this->colorContour = t.colorContour;
        this->point = t.point;
        //Calcul du point RotationCenter
        this->RotationCenter.setAbs(point.getAbs() + size/2);
        this->RotationCenter.setOrd(point.getOrd() + size/2);
        Logger::log("Opérateur d'assignation du Text : " + text);
    }else{
        Logger::log("Opérateur d'assignation du Text sur lui-même : " + text);
    }
    return *this;
};

/* Méthodes */
//Getters
string Text::getText() const{
    return text;
};
string Text::getFont() const{
    return font;
};
int Text::getSize() const{
    return size;
};
int Text::getThickness() const{
    return thickness;
};
Color Text::getColorFond(){
    return colorFond;
};
Color Text::getColorContour(){
    return colorContour;
};
Point Text::getPoint() const{
    return point;
};
Point Text::getRotationCenter() const{
    return RotationCenter;
};
//Aire
double Text::aire(){
    return 0;
};
//Information
void Text::info(){
    cout << "Text : " << getText() << endl;
    cout << "Font : " << getFont() << endl;
    cout << "Size : " << getSize() << endl;
    cout << "Thickness : " << getThickness() << endl;
    cout << "ColorFond : " << getColorFond().RGBAtoString() << endl;
    cout << "ColorContour : " << getColorContour().RGBAtoString() << endl;
    cout << "Point : (" << point.getAbs() << "," << point.getOrd() << ")" << endl;
    cout << "Selected : " << this->selected << endl;
};
//Setters
void Text::setText(string t){
    text = t;
    //Recalcule du point RotationCenter
    RotationCenter.setAbs(point.getAbs() + size/2);
    RotationCenter.setOrd(point.getOrd() + size/2);

};
void Text::setFont(string f){
    this->font = f;
    //Recalcule du point RotationCenter
    this->RotationCenter.setAbs(this->point.getAbs() + size/2);
    this->RotationCenter.setOrd(this->point.getOrd() + size/2);
};
void Text::setThickness(int th){
    this->thickness = th;
    //Recalcule du point RotationCenter
    this->RotationCenter.setAbs(this->point.getAbs() + size/2);
    this->RotationCenter.setOrd(this->point.getOrd() + size/2);
};
//Surcharge de l'opérateur <<
SVGstream& operator<<(SVGstream &os, const Text &t){
    os << "\n<text x=\"" << t.point.getAbs() << "\" y=\"" << t.point.getOrd() << "\" font-family=\"" << t.font << "\" font-size=\"" << t.size << "\" fill=\"RGBA(" << t.colorFond.RGBAtoString() << ")\" stroke=\"RGBA(" << t.colorContour.RGBAtoString() << ")\" transform=\"rotate(" << t.RotationAngle << " " << t.RotationCenter.getAbs() << " " << t.RotationCenter.getOrd() << ")\">" << t.text << "</text>";
    return os;
};
//print
void Text::print(SVGstream& os){
    Logger::log("Print du Text : " + text);
    os << *this;
};
//printTikZ
void Text::printTikZ(TikZstream& os){
    Logger::log("Print du Text : " + text);
    os << "\n\\node[fill={rgb:red," << this->colorFond.getRed()
       << ";green," << this->colorFond.getGreen()
       << ";blue," << this->colorFond.getBlue()
       << "}, opacity=" << this->colorFond.getAlpha() 
       << ", text=" << font << "] at (" << point.getAbs() 
       << "," << point.getOrd() << ") {" << text << "};\n";
}
//Type du texte
Text::ShapeType Text::getType(){
    return ShapeType::Text;
};
//Clone l'objet
std::unique_ptr<Geom2D> Text::clone() const{
    return std::make_unique<Text>(*this);
}
//Vérifie si le text est en dehors du canva
bool Text::isOutside(double width, double height){
    if(point.getAbs() < 0 || point.getAbs() + size > width || point.getOrd() < 0 || point.getOrd() + size > height){
        return true;
    }
    return false;
};
//Vérifie si le point est du texte
bool Text::isInside(Point point){
    if(point.getAbs() >= this->point.getAbs() && point.getAbs() <= this->point.getAbs() + size && point.getOrd() >= this->point.getOrd() && point.getOrd() <= this->point.getOrd() + size){
        return true;
    }
    return false;
};

/* Méthodes virtuelles pures */
// Translation
void Text::translation(const int x, const int y){
    Logger::log("Translation du Text : " + text);
    this->point.setAbs(this->point.getAbs() + x);
    this->point.setOrd(this->point.getOrd() + y);
    //Recalcule du point RotationCenter
    this->RotationCenter.setAbs(this->point.getAbs() + size/2);
    this->RotationCenter.setOrd(this->point.getOrd() + size/2);
};
// Rotation
void Text::rotation(const int angle){
    Logger::log("Rotation du Text : " + text);
    this->RotationAngle += angle;
    //Recalcule du point RotationCenter
    this->RotationCenter.setAbs(this->point.getAbs() + size/2);
    this->RotationCenter.setOrd(this->point.getOrd() + size/2);
};
// Scaling
void Text::scaling(const double scaleFactor){
    Logger::log("Scaling du Text : " + text);
    this->size *= int(scaleFactor);
    //Recalcule du point RotationCenter
    this->RotationCenter.setAbs(this->point.getAbs() + size/2);
    this->RotationCenter.setOrd(this->point.getOrd() + size/2);
};
// Remplissage
void Text::fill(const Color color){
    Logger::log("Remplissage du Text : " + text);
    this->colorFond = color;
};
// Contour
void Text::contour(const Color color){
    Logger::log("Contour du Text : " + text);
    this->colorContour = color;
};




