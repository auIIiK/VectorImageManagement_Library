#include "../include/Color.h"

#include <iostream>
#include <string>

using namespace std;

/* Constructeurs */
//Constructeur par défaut
Color::Color(){
    Logger::log("Constructeur par défaut de Color.");
    red = 255;
    green = 255;
    blue = 255;
    alpha = 1.0;
}
//Constructeur avec paramètres sous forme RGB
Color::Color(uint8_t r, uint8_t g, uint8_t b){
    Logger::log("Constructeur de Color de valeur RGB : (" + to_string(r) + "," + to_string(g) + "," + to_string(b) + ").");
    red = r;
    green = g;
    blue = b;
    alpha = 1.0;
}
//Constructeur avec paramètres sous forme RGBA
Color::Color(uint8_t r, uint8_t g, uint8_t b, float a){
    Logger::log("Constructeur de Color de valeur RGBA : (" + to_string(r) + "," + to_string(g) + "," + to_string(b) + "," + to_string(a) + ").");
    red = r;
    green = g;
    blue = b;
    alpha = a;
}
//Constructeur par copie
Color::Color(const Color &c){
    Logger::log("Constructeur par copie de Color de valeur RGBA : (" + c.RGBAtoString() + ").");
    red = c.red;
    green = c.green;
    blue = c.blue;
    alpha = c.alpha;
}

/* Destructeur */
Color::~Color(){
    Logger::log("Destructeur de Color de valeur RGBA : (" + RGBAtoString() + ").");
}

/* Opérateurs d'assignation */
Color& Color::operator=(const Color &c){
    red = c.red;
    green = c.green;
    blue = c.blue;
    alpha = c.alpha;
    return *this;
}

/* Méthodes */
//Getters
uint8_t Color::getRed() const{
    return red;
}
uint8_t Color::getGreen() const{
    return green;
}
uint8_t Color::getBlue() const{
    return blue;
}
float Color::getAlpha() const{
    return alpha;
}

//Setters
void Color::setRed(uint8_t r){
    red = r;
}
void Color::setGreen(uint8_t g){
    green = g;
}
void Color::setBlue(uint8_t b){
    blue = b;
}
void Color::setAlpha(float a){
    alpha = a;
}

//Renvoie la valeur RGBA de la couleur
uint32_t Color::getRGB() const{
    return (uint32_t)(red << 24) | (uint32_t)(green << 16) | (uint32_t)(blue << 8) | (uint8_t)(alpha * 255);
}

//Renvoie la valeur RGBA de la couleur sous forme de chaîne de caractères
string Color::RGBAtoString() const{
    return to_string(red) + "," + to_string(green) + "," + to_string(blue) + "," + to_string(alpha);
}
