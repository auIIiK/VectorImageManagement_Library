#ifndef _COLOR_H_
#define _COLOR_H_

#include "Logger.h"

#include <cstdint>
#include <string>

// Classe représentant une couleur sous forme de triplet RGB (Red, Green, Blue) ou RGBA (Red, Green, Blue, Alpha)
class Color {

    private :

        /* Attributs de la couleur */
        uint8_t red; //composante rouge (valeur entre 0 et 255)
        uint8_t green; //composante verte (valeur entre 0 et 255)
        uint8_t blue; //composante bleue (valeur entre 0 et 255)
        float alpha; //composante alpha (transparence) (0.0 = transparent, 1.0 = opaque)

    public :

        /* Constructeurs */
        Color(); //Constructeur par défaut
        Color(uint8_t r, uint8_t g, uint8_t b); //Constructeur avec paramètres sous forme RGB
        Color(uint8_t r, uint8_t g, uint8_t b, float a); //Constructeur avec paramètres sous forme RGBA
        Color(const Color &c); //Constructeur par copie

        /* Destructeur */
        ~Color();

        /* Opérateurs d'assignation */
        Color& operator=(const Color &c);

        /* Méthodes */
        //Getters
        uint8_t getRed() const;
        uint8_t getGreen() const;
        uint8_t getBlue() const;
        float getAlpha() const;
        //Setters
        void setRed(uint8_t r);
        void setGreen(uint8_t g);
        void setBlue(uint8_t b);
        void setAlpha(float a);
        //Renvoie la valeur RGBA de la couleur
        uint32_t getRGB() const;
        //Renvoie la valeur RGBA de la couleur sous forme de chaîne de caractères
        std::string RGBAtoString() const;


};

#endif // _COLOR_H_