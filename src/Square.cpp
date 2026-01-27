#include "../include/Square.h"

#include <iostream>
#include <cmath>

using namespace std;

/* Constructeurs */
//Constructeur par défaut
Square::Square() : Rectangle(Point(1, 2), 4, 4, Color(0, 0, 0), Color(255, 255, 255)) {
    Logger::log("Constructeur par défaut du Square.");
}

//Constructeur par initialisation
Square::Square(Point point, float cote, Color colorFond, Color colorContour) : Rectangle(point, cote, cote, colorFond, colorContour) {
    Logger::log("Constructeur par initialisation du Square.");
}
//Constructeur par copie
Square::Square(const Square &s) : Rectangle(s) {
    Logger::log("Constructeur par copie du Square.");
}

/* Opérateur d'assignation */
Square& Square::operator=(const Square &s){
    if(this != &s){
        Rectangle::operator=(s);
        Logger::log("Opérateur d'assignation du Square.");
    }else{
        Logger::log("Opérateur d'assignation du Square sur lui-même.");
    }
    return *this;
}

/* Destructeur */
Square::~Square(){
   Logger::log("Destructeur du Square.");
}