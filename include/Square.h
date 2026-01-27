#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Rectangle.h"
#include "Logger.h"

class Square : public Rectangle{

    public :
        /* Constructeur */
        Square(); //Constructeur par défault
        Square(Point point, float cote, Color colorFond, Color colorContour); //Constructeur par initialisation
        Square(const Square &s); //Constructeur par copie

        /* Opérateur d'assignation */
        Square& operator=(const Square &s);

        /* Destructeur */
        ~Square();

};

#endif // _SQUARE_H_