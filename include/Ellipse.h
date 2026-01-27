#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include "Fill.h"
#include "Point.h"
#include "Transform.h"
#include "Geom2D.h"
#include "Logger.h"

class Ellipse : public Geom2D, public Fill {

    private :
        /* Attributs */
        Color colorFond;
        Color colorContour;
        Point point;
        double rayonX;
        double rayonY;
        int RotationAngle = 0;

    public : 
        /* Constructeur */
        Ellipse(); //Constructeur par défault
        Ellipse(Point point, Color colorFond, Color colorContour, double rayonX, double rayonY); //Constructeur par initialisation
        Ellipse(const Ellipse &e); //Constructeur par copie

        /* Opéarteur d'assignation */
        Ellipse& operator=(const Ellipse &e);

        /* Destructeur */
        ~Ellipse();

        /* Méthodes */
        //Getter
        Point getPoint();
        Color getColorFond() override;
        Color getColorContour() override;
        double getRayonX();
        double getRayonY();
        //Aire de l'ellipse
        double aire() override;
        //Information de l'ellipse
        void info() override;
        //Type de l'ellipse
        ShapeType getType() override;
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        //Vérifie si l'ellipse est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans l'ellipse
        bool isInside(Point point) override;
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, const Ellipse &e);
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

#endif // _ELLIPSE_H_