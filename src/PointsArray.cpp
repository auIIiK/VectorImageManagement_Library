#include "../include/PointsArray.h"

using namespace std;

/* Constructeur */
// Constructeur par défault
PointsArray::PointsArray(){
    Logger::log("Constructeur par défaut de PointsArray.");
    this->tailletab = 0;
    this->tab = NULL;
}
// Constructeur par initialisation
PointsArray::PointsArray(int taille, Point *tab){
    Logger::log("Constructeur de PointsArray de taille : " + to_string(taille) + ".");
    this->tailletab = taille;
    this->tab = tab;
}
// Constructeur par copie
PointsArray::PointsArray(const PointsArray &p){
    Logger::log("Constructeur par copie de PointsArray de taille : " + to_string(p.tailletab) + ".");
    this->tailletab = p.tailletab;
    // Faire une copie profonde du tableau de points
    this->tab = new Point[static_cast<size_t>(this->tailletab)];
    for(int i = 0; i < this->tailletab; i++){
        this->tab[i] = p.tab[i];
    }
}

/* Opérateur d'assignation */
PointsArray& PointsArray::operator=(const PointsArray &p){
    Logger::log("Opérateur d'assignation de PointsArray de taille : " + to_string(p.tailletab) + ".");
    if(this != &p){
        this->tailletab = p.tailletab;
        this->tab = p.tab;
    }
    return *this;
}

/* Destructeur */
PointsArray::~PointsArray(){
    Logger::log("Destructeur de PointsArray de taille : " + to_string(this->tailletab) + ".");
    delete[] this->tab;
}

/* Getter */
//Méthode qui retourne la taille du tableau de points.
int PointsArray::getTailleTab() const{
    return this->tailletab;
}
//Méthode qui retourne le pointeur vers le tableau de points.
Point* PointsArray::getTab() const{
    return this->tab;
}
//Méthode qui retourne le pointeur vers le point d'indice i du tableau.
Point* PointsArray::getPoint(int i) const{
    return &this->tab[i];
}

/* Setter */
//Méthode qui modifie la taille du tableau de points.
void PointsArray::setTailleTab(int taille){
    this->tailletab = taille;
}
void PointsArray::setTab(Point *newTab) {
    // Libérer la mémoire de l'ancien tableau si elle existe
    if (this->tab != nullptr) {
        delete[] this->tab;
    }

    // Mettre à jour le pointeur pour pointer vers le nouveau tableau
    this->tab = newTab;
}


/* Méthodes virtuelles pures */
void PointsArray::translation(const int /* x */, const int /* y */){
    // Ne rien faire
}
void PointsArray::rotation(const int /* angle */){
    // Ne rien faire
}
void PointsArray::scaling(const double /* scaleFactor */){
    // Ne rien faire
}
void PointsArray::fill(const Color /* color */){
    // Ne rien faire
}
void PointsArray::contour(const Color /* color */){
    // Ne rien faire
}

