#ifndef _GEOM2D_H_
#define _GEOM2D_H_

#include "Point.h"
#include "Transform.h"
#include "SVGstream.h"
#include "TikZstream.h"
#include "Logger.h"

#include <memory>


class Geom2D : public Transform, public Point {

    public :
        /* Enumération des types de formes */
        enum class ShapeType: uint64_t {
            Stroke    = 1 << 0,  // = 0000 0001 = 0x01 =   1
            Triangle  = 1 << 1,  // = 0000 0010 = 0x02 =   2
            Rectangle = 1 << 2,  // = 0000 0100 = 0x04 =   4
            Pentagon  = 1 << 3,  // = 0000 1000 = 0x08 =   8
            Hexagon   = 1 << 4,  // = 0001 0000 = 0x10 =  16
            Heptagon  = 1 << 5,  // = 0010 0000 = 0x20 =  32
            Octogon   = 1 << 6,  // = 0100 0000 = 0x40 =  64
            Ellipsis  = 1 << 7,  // = 1000 0000 = 0x80 = 128
            Complexe  = 1 << 8,  // = 0001 0000 0000 = 0x100 = 256
            Text      = 1 << 9,  // = 0010 0000 0000 = 0x200 = 512
            All       = Stroke | Triangle | Rectangle | Pentagon | Hexagon | Heptagon | Octogon | Ellipsis | Complexe | Text
        };

        /* attribut minimum requis pour les formes */
        std::string name;
        bool selected;
        ShapeType type;


        /* Méthode */
        virtual double aire() = 0;
        virtual void info() = 0;
        virtual ~Geom2D() {};
        virtual ShapeType getType() = 0;
        virtual Color getColorContour() = 0;
        virtual Color getColorFond() = 0;
        virtual std::unique_ptr<Geom2D> clone() const = 0;
        //Méthode qui verifie si la forme est à l'extérieur de la zone de dessin
        virtual bool isOutside(double width, double height) = 0;
        //Méthode qui verifie si un point est à l'intérieur de la forme
        virtual bool isInside(Point point) = 0;
        //printSVG
        virtual void print(SVGstream& os) = 0;
        //printTikZ
        virtual void printTikZ(TikZstream& os) = 0;

        //Surcharge de l'opérateur << pour SVGstream
        friend SVGstream& operator<<(SVGstream& os, Geom2D& g){
            g.print(os);
            return os;
        }
        //Surcharge de l'opérateur << pour TikZstream
        friend TikZstream& operator<<(TikZstream& os, Geom2D& g){
            g.printTikZ(os);
            return os;
        }


};

#endif // _GEOM2D_H_