#ifndef _POINT_H_
#define _POINT_H_

#include "Logger.h"
#include <math.h>

class Point{

    private:

        /* Attributs du point */
        int abs; //absisse
        int ord; //ordonnée

    public:

        /* Constructeurs */
        Point(); //Constructeur par défaut
        Point(int x, int y); //Constructeur avec paramètres
        Point(const Point &p); //Constructeur par copie

        /* Destructeur */
        ~Point();

        /* Opérateurs d'assignation */
        Point& operator=(const Point &p);

        /* Méthodes */
        //Getters
        int getAbs() const;
        int getOrd() const;
        //Setters
        void setAbs(int x);
        void setOrd(int y);
        //Distance entre deux points
        double distance(const Point &p) const;

};

#endif // _POINT_H_