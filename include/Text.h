#ifndef _TEXT_H_
#define _TEXT_H_

#include "Fill.h"
#include "Point.h"
#include "Transform.h"
#include "Geom2D.h"
#include "Logger.h"

using namespace std;

class Text : public Geom2D, public Fill{

    private :

        /* Attributs */
        string text;
        string font;
        int size;
        int thickness;
        Color colorFond;
        Color colorContour;
        Point point;
        Point RotationCenter;
        int RotationAngle = 0;

    public :

        /* Constructeur */
        //Constructeur par défaut
        Text();
        //Constructeur avec paramètres
        Text(string t, string f, int s, int th, Color cF, Color cC, Point p);
        //Constructeur par copie
        Text(const Text &t);

        /* Destructeur */
        ~Text();

        /* Opérateurs d'assignation */
        Text& operator=(const Text &t);

        /* Méthodes */
        //Getters
        string getText() const;
        string getFont() const;
        int getSize() const;
        int getThickness() const;
        Color getColorFond() override;
        Color getColorContour() override;
        Point getPoint() const;
        Point getRotationCenter() const;
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        //Vérifie si le text est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans le text
        bool isInside(Point point) override;
        //Type du texte
        ShapeType getType() override;
        double aire() override;
        void info() override;

        //Setters
        void setText(string t);
        void setFont(string f);
        void setThickness(int th);
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, const Text &t);
        //print
        void print(SVGstream& os) override;
        //printTikZ
        void printTikZ(TikZstream& os) override;

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

#endif // _TEXT_H_