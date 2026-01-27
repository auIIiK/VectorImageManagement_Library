#ifndef POINTSARRAY_H
#define POINTSARRAY_H

#include <iostream>
#include <fstream>
#include <string>

#include "Transform.h"
#include "Point.h"
#include "Logger.h"

class PointsArray : public Transform{

    private:
        int tailletab;
        Point *tab;

    public:
        /* Constructeur */
        PointsArray();
        PointsArray(int taille, Point *tab);
        PointsArray(const PointsArray &p);

        /* Opérateur d'assignation */
        PointsArray& operator=(const PointsArray &p);

        /* Destructeur */
        virtual ~PointsArray();

        /* Getter */
        //Méthode qui retourne la taille du tableau de points.
        int getTailleTab() const;
        //Méthode qui retourne le pointeur vers le tableau de points.
        Point* getTab() const;
        //Méthode qui retourne le pointeur vers le point d'indice i du tableau.
        Point* getPoint(int i) const;

        /* Setter */
        //Méthode qui modifie la taille du tableau de points.
        void setTailleTab(int taille);
        //Méthode qui modifie le pointeur vers le tableau de points.
        void setTab(Point *tab);

        /* Méthodes virtuelles pures */
        // Translation
        virtual void translation(const int x, const int y) override;
        // Rotation
        virtual void rotation(const int angle) override;
        // Scaling
        virtual void scaling(const double scaleFactor) override;
        // Remplissage
        virtual void fill(const Color color) override;
        // Contour
        virtual void contour(const Color color) override;


};

#endif // POINTSARRAY_H