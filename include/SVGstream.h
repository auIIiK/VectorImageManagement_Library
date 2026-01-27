#ifndef SVGSTREAM_H
#define SVGSTREAM_H

#include <string>
#include <iostream>
#include <fstream>

#include "Color.h"
#include "Logger.h"

class SVGstream{

    protected:
        std::ofstream fileStream; // Flux de fichier
        std::string filename; // Nom du fichier
        double height; // Hauteur
        double width; // Largeur
        Color colorFond; // Couleur de fond
    public:
        /* Constructeur  */
        //Constructeur avec paramètre
        SVGstream(const std::string &filename, const double height, const double width, Color colorFond, bool PureSvg);

        //Destructeur
        ~SVGstream();

        /* Fonctions */
        //Méthode de fermeture 
        void close();
        //Méthode d'ouverture
        bool open(const std::string &filename, bool PureSvg);
        //Surcharge de l'opérateur <<
        friend SVGstream& operator<<(SVGstream& stream, const char *str);
        friend SVGstream& operator<<(SVGstream& stream, float val);
        friend SVGstream& operator<<(SVGstream& stream, std::string str);

};

#endif /* SVGSTREAM_H */