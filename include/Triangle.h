#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Fill.h"
#include "Point.h"
#include "Transform.h"
#include "Geom2D.h"
#include "Logger.h"

class Triangle : public Geom2D, public Fill{
    private :
        /* Attributs */
        Color colorFond;
        Color colorContour;
        Point point1;
        Point point2;
        Point point3;
        Point rotationCenter;
        int RotationAngle = 0;

    public :
        /* Constructeur */
        Triangle(); //Constructeur par défault
        Triangle(Point point1, Point point2, Point point3, Color colorFond, Color colorContour); //Constructeur par initialisation
        Triangle(const Triangle &t); //Constructeur par copie

        /* Opérateur d'assignation */
        Triangle& operator=(const Triangle &t);

        /* Destructeur */
        ~Triangle();

        /* Méthodes */
        //Getter
        Point getPoint1();
        Point getPoint2();
        Point getPoint3();
        Color getColorFond() override;
        Color getColorContour() override;
        //Aire du triangle
        double aire() override;
        //Information du triangle
        void info() override;
        //Type du triangle
        ShapeType getType() override;
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, Triangle &t);
        //print
        void print(SVGstream& os) override;
        //printTikZ
        void printTikZ(TikZstream& os) override;
        //Vérifie si le triangle est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans le triangle
        bool isInside(Point point) override;
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        /* Méthodes virtuel pure */
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


#endif // _TRIANGLE_H_