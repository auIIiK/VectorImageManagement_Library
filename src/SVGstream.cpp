#include "../include/SVGstream.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/* Fonction */
//Fermeture
void SVGstream::close() {
    Logger::log("Fermeture du SVGstream");
    if (fileStream.is_open()) { // Vérifier si le fichier est ouvert
        fileStream << "</svg>"; // Écrire la fin du fichier SVG
        fileStream.close(); // Fermer le fichier
    }
}
//Ouverture
bool SVGstream::open(const std::string &filename, bool PureSvg){
    close();
    Logger::log("Ouverture du SVGstream");
    fileStream.open(filename, std::ios::out | std::ios::trunc);
    bool status = fileStream.is_open();

    if (status) {
        if (PureSvg) {
            fileStream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\" style=\"background-color : RGBA(" << colorFond.RGBAtoString() << ");\">\n";
        } else {
            fileStream << "<!doctype html><svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\" style=\"background-color : RGBA(" << colorFond.RGBAtoString() << ");\">\n";
        }
    }

    return status;
}

/* Constructeur */
//Constructeur avec paramètre du SVGstream
SVGstream::SVGstream(const std::string &filename, const double height, const double width, Color colorFond, bool PureSvg) {
    Logger::log("Constructeur du SVGstream");
    this->filename = filename; // Stocker le nom du fichier
    fileStream.open(filename); // Ouvrir le fichier

    if (!fileStream) { // Vérifier si le fichier a été ouvert correctement
        cerr << "Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

    if (PureSvg) { // Si PureSvg est vrai, écrire seulement l'en-tête SVG avec les dimensions et la couleur de fond
        fileStream << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\" style=\"background-color : RGBA(" << colorFond.RGBAtoString() << ");\">\n";
        
    } else { // Sinon, écrire l'en-tête HTML et SVG
        fileStream << "<!doctype html><svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\" style=\"background-color : RGBA(" << colorFond.RGBAtoString() << ");\">\n";
    }
}

/* Destructeur */
SVGstream::~SVGstream(){
    Logger::log("Destructeur du SVGstream");
    if (fileStream.is_open()) { // Vérifier si le fichier est ouvert
        fileStream << "\n</svg>"; // Écrire la fin du fichier SVG
        fileStream.close(); // Fermer le fichier
    }
}

/* Autre fonctions */
//Surcharge de l'opérateur <<
SVGstream& operator<<(SVGstream& stream, const char *str){
    stream.fileStream << str;
    return stream;
}
SVGstream& operator<<(SVGstream& stream, float val){
    stream.fileStream << val;
    return stream;
}
SVGstream& operator<<(SVGstream& stream, string str){
    stream.fileStream << str;
    return stream;
}








