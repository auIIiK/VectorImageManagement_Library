#ifndef _DISC_H_
#define _DISC_H_

#include "Fill.h"
#include "Point.h"
#include "Transform.h"
#include "Geom2D.h"
#include "Logger.h"

class Disc : public Geom2D, public Fill{

    private :
        /* Attributs */
        Point point;
        Color colorFond;
        Color colorContour;
        double rayon;

    public :
        /* Constructeur */
        Disc(); //Constructeur par défault
        Disc(Point point, Color colorFond, Color colorContour, double rayon); //Constructeur par initialisation
        Disc(const Disc &d); //Constructeur par copie

        /* Opérateur d'assignation */
        Disc& operator=(const Disc &d);

        /* Destructeur */
        ~Disc();

        /* Méthodes */
        //Getter
        Point getPoint();
        Color getColorFond() override;
        Color getColorContour() override;
        double getRayon();
        //Aire du disc
        double aire() override;
        //Information du disc
        void info() override;
        //Type du disc
        ShapeType getType() override;
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        //Vérifie si le disc est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans le disc
        bool isInside(Point point) override;
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, Disc &d);
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


#endif // _DISC_H_