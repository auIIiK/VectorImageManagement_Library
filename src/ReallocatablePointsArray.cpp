#include "../include/ReallocatablePointsArray.h"

#include <iostream>
#include <memory>


using namespace std;

/* Constructeur */
// Constructeur par défault
ReallocatablePointsArray::ReallocatablePointsArray(){
    Logger::log("Constructeur par défaut de ReallocatablePointsArray.");
    this->setTailleTab(0);
    this->setTab(NULL);
    this->setTailleAllouee(0);
}
// Constructeur par initialisation
ReallocatablePointsArray::ReallocatablePointsArray(int taille, Point *tab, int tailleallouee){
    Logger::log("Constructeur de ReallocatablePointsArray de taille : " + to_string(taille) + ".");
    this->setTailleTab(taille);
    this->setTab(tab);
    this->setTailleAllouee(tailleallouee);
}
// Constructeur par copie
ReallocatablePointsArray::ReallocatablePointsArray(const ReallocatablePointsArray &p) : PointsArray(p) {
    Logger::log("Constructeur par copie de ReallocatablePointsArray de taille : " + to_string(p.getTailleTab()) + ".");
    //copie profonde
    this->setTailleTab(p.getTailleTab());
    Point *tab = new Point[static_cast<size_t>(p.getTailleTab())];
    for(int i = 0; i < p.getTailleTab(); i++){
        tab[i] = p.getTab()[i];
    }
    this->setTab(tab);
    this->setTailleAllouee(p.getTailleAllouee());
}

/* Opérateur d'assignation */
ReallocatablePointsArray& ReallocatablePointsArray::operator=(const ReallocatablePointsArray &p){
    Logger::log("Opérateur d'assignation de ReallocatablePointsArray de taille : " + to_string(p.getTailleTab()) + ".");
    if(this != &p){
        //copie profonde
        this->setTailleTab(p.getTailleTab());
        Point *tab = new Point[static_cast<size_t>(p.getTailleTab())];
        for(int i = 0; i < p.getTailleTab(); i++){
            tab[i] = p.getTab()[i];
        }
        this->setTab(tab);
        this->setTailleAllouee(p.getTailleAllouee());
    }
    return *this;
}

/* Destructeur */
ReallocatablePointsArray::~ReallocatablePointsArray(){
    Logger::log("Destructeur de ReallocatablePointsArray de taille : " + to_string(this->getTailleTab()) + ".");
}

/* Getter */
//Méthode qui retourne la taille allouée du tableau de points.
int ReallocatablePointsArray::getTailleAllouee() const{
    return this->tailleallouee;
}

/* Setter */
//Méthode qui modifie la taille allouée du tableau de points.
void ReallocatablePointsArray::setTailleAllouee(int tailleallouee){
    this->tailleallouee = tailleallouee;
}

/* Méthode */
//Méthode qui ajoute un point au tableau de points.
void ReallocatablePointsArray::addPoint(Point p) {
    Logger::log("Ajout d'un point au tableau de points de ReallocatablePointsArray.");
    if (this->getTailleTab() == this->getTailleAllouee()) {
        int nouvelleTaille = this->getTailleAllouee() + 1;
       Point *tab = new Point[static_cast<size_t>(nouvelleTaille)];

        for (int i = 0; i < this->getTailleTab(); i++) {
            tab[i] = this->getTab()[i];
        }
        tab[this->getTailleTab()] = p;

        // Met à jour les propriétés de l'objet
        this->setTab(tab);
        this->setTailleAllouee(nouvelleTaille);
        this->setTailleTab(this->getTailleTab() + 1);
    } else {
        this->getTab()[this->getTailleTab()] = p;
        this->setTailleTab(this->getTailleTab() + 1);
    }
}

void ReallocatablePointsArray::removePoint(int i){
    Logger::log("Suppression d'un point du tableau de points de ReallocatablePointsArray.");
    if(i < this->getTailleTab()){
        for(int j = i; j < this->getTailleTab() - 1; j++){
            this->getTab()[j] = this->getTab()[j+1];
        }
        this->setTailleTab(this->getTailleTab() - 1);
    }
    else{
        std::cerr << "Indice invalide" << std::endl;
    }
}

