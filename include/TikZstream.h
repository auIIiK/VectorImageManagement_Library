#ifndef TIKZSTREAM_H
#define TIKZSTREAM_H

#include <string>
#include <iostream>
#include <fstream>
#include "Color.h"
#include "Logger.h"

class TikZstream{

    protected:
        std::ofstream fileStream; // Flux de fichier
        std::string filename; // Nom du fichier
        double height; // Hauteur
        double width; // Largeur
        Color colorFond; // Couleur de fond
    public:
        /* Constructeur  */
        //Constructeur avec paramètre
        TikZstream(const std::string &filename, const double height, const double width, Color colorFond);

        //Destructeur
        ~TikZstream();

        /* Fonctions */
        //Méthode de fermeture 
        void close();
        //Méthode d'ouverture
        bool open(const std::string &filename);
        //Surcharge de l'opérateur <<
        friend TikZstream& operator<<(TikZstream& stream, const char *str);
        friend TikZstream& operator<<(TikZstream& stream, float val);
        friend TikZstream& operator<<(TikZstream& stream, std::string str);

};

#endif /* TIKZSTREAM_H */