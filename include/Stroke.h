#ifndef STROKE_H
#define STROKE_H

#include "Fill.h"
#include "Point.h"
#include "Transform.h"
#include "Geom2D.h"
#include "Logger.h"

class Stroke : public Geom2D, public Fill{

    private :
        /* Attributs */
        Point point1;
        Point point2;
        Color color;
        Point rotationCenter;
        int RotationAngle = 0;

    public :
        /* Constructeur */
        Stroke(); //Constructeur par défault
        Stroke(Point point1, Point point2, Color colorContour); //Constructeur par initialisation
        Stroke(const Stroke &s); //Constructeur par copie

        /* Opérateur d'assignation */
        Stroke& operator=(const Stroke &s);

        /* Destructeur */
        ~Stroke();

        /* Méthodes */
        //Getter
        Point getPoint1();
        Point getPoint2();
        Color getColorContour() override;
        Color getColorFond() override;
        //Longueur du trait
        double longueur();
        //Aire du trait
        double aire() override;
        //Information du trait
        void info() override;
        //Type du trait
        ShapeType getType() override;
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        //Vérifie si le trait est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans le trait
        bool isInside(Point point) override;
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, Stroke &s);
        //print
        void print(SVGstream& os) override;
        //printTikZ
        void printTikZ(TikZstream& os) override;

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

#endif // STROKE_H