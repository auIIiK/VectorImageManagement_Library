#include "../include/Point.h"

#include <iostream>

using namespace std;

/* Constructeurs */
//Constructeur par défaut
Point::Point(){
    abs = 0;
    ord = 0;
}

//Constructeur avec paramètres
Point::Point(int x, int y){
    abs = x;
    ord = y;
}

//Constructeur par copie
Point::Point(const Point &p){
    abs = p.abs;
    ord = p.ord;
}

/* Destructeur */
Point::~Point(){
}

/* Opérateurs d'assignation */
Point& Point::operator=(const Point &p){
    //copie profonde
    abs = p.abs;
    ord = p.ord;
    return *this;
    
}

/* Méthodes */
//Getters
int Point::getAbs() const{
    return abs;
}
int Point::getOrd() const{
    return ord;
}
//Setters
void Point::setAbs(int x){
    abs = x;
}
void Point::setOrd(int y){
    ord = y;
}
//Distance entre deux points
double Point::distance(const Point &p) const{
    return sqrt(pow(p.abs - abs, 2) + pow(p.ord - ord, 2));
}