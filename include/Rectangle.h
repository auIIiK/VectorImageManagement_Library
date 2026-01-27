#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Fill.h"
#include "Point.h"
#include "Transform.h"
#include "Geom2D.h"
#include "Logger.h"

class Rectangle : public Geom2D, public Fill{

    private :
        /* Attributs */
        Color colorFond;
        Color colorContour;
        Point point;
        float hauteur;
        float largeur;
        Point rotationCenter;
        int RotationAngle = 0;

    public :
        /* Constructeur */
        Rectangle(); //Constructeur par défault
        Rectangle(Point point, float hauteur, float largeur, Color colorFond, Color colorContour); //Constructeur par initialisation
        Rectangle(const Rectangle &r); //Constructeur par copie

        /* Opérateur d'assignation */
        Rectangle& operator=(const Rectangle &r);

        /* Destructeur */
        ~Rectangle();

        //Getter
        Point getPoint();
        float getHauteur();
        float getLargeur();
        Color getColorFond() override;
        Color getColorContour() override;
        //Aire du rectangle
        double aire() override;
        //Information du rectangle
        void info() override;
        //Getter du type
        ShapeType getType() override;
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        //Vérifie si le rectangle est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans le rectangle
        bool isInside(Point point) override;
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, Rectangle &r);
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

#endif // _RECTANGLE_H_