#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "ReallocatablePointsArray.h"
#include "Geom2D.h"
#include "Logger.h"

#include <memory>

class Polygon : public Geom2D, public ReallocatablePointsArray{

    private :
        /* Attributs */
       std::shared_ptr<ReallocatablePointsArray> tabPoints;
        Color colorFond;
        Color colorBorder;
        int rotationAngle = 0;
        Point rotationCenter;
    
    public :
        /* Constructeur */
        Polygon(Color colorFond, Color ColorBorder);
        Polygon(const Polygon &p);

        //Opérateur d'assignation
        Polygon& operator=(const Polygon &p);

        /* Destructeur */
        ~Polygon();

        /* Méthode */
        //getters
       std::shared_ptr<ReallocatablePointsArray> getTabPoint() const;
        Color getColorFond() override;
        Color getColorContour() override;
        //Aire du polygon
        double aire() override;
        //Information du polygon
        void info() override;
        //Type du polygon
        ShapeType getType() override;
        std::string ShapeTypeToString(ShapeType type);
        //Clone l'objet
        std::unique_ptr<Geom2D> clone() const override;
        //Vérifie si le polygon est en dehors du canva
        bool isOutside(double width, double height) override;
        //Vérifie si un point est dans le polygon
        bool isInside(Point point) override;
        //Surchage de l'opérateur <<
        friend SVGstream& operator<<(SVGstream &os, const Polygon &p);
        //print
        void print(SVGstream& os) override;
        //printTikZ
        void printTikZ(TikZstream& os) override;
        //Centre du polygon
        Point center();
        //Rajout de points
        void addPoint(const Point p);
        //Suppression de points
        void removePoint(const int i);

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

#endif // _POLYGON_H_