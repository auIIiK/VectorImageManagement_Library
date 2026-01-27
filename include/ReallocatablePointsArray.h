#ifndef REALLOCATABLEPOINTSARRAY_H
#define REALLOCATABLEPOINTSARRAY_H

#include <iostream>
#include <fstream>
#include <string>

#include "PointsArray.h"
#include "Logger.h"

/* Une classe ReallocatablePointsArray qui hérite de PointsArray et qui permet de rendre le tableau de points réallouable (l'ajout de points supplémentaires est possible). Sa principale différence est qu'elle contient trois champs : la taille du tableau, le pointeur vers un tableau de points, et la taille allouée pour le tableau de points. Pour un tableau de taille variable, cela permet d'allouer un tableau un peu plus grand, et d'y placer de nouveaux points jusqu'à ce qu'il n'y ait plus de place. On alloue alors un tableau un peu plus grand, ce qui permet de continuer à ajouter des points. */

class ReallocatablePointsArray : public PointsArray{

    private :
        int tailleallouee;
    public :
        /* Constructeur */
        ReallocatablePointsArray();
        ReallocatablePointsArray(int taille, Point *point, int tailleallouee);
        ReallocatablePointsArray(const ReallocatablePointsArray &p);

        /* Opérateur d'assignation */
        ReallocatablePointsArray& operator=(const ReallocatablePointsArray &p);

        /* Destructeur */
        ~ReallocatablePointsArray();

        /* Getter */
        //Méthode qui retourne la taille allouée du tableau de points.
        int getTailleAllouee() const;

        /* Setter */
        //Méthode qui modifie la taille allouée du tableau de points.
        void setTailleAllouee(int tailleallouee);

        /* Méthode */
        //Ajout d'un point au tableau de points.
        void addPoint(Point p);
        //Suppression d'un point du tableau de points.
        void removePoint(int i);

};

#endif // REALLOCATABLEPOINTSARRAY_H