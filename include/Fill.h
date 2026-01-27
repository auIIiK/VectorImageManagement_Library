#ifndef _FILL_H_
#define _FILL_H_

#include "Color.h"
#include "Logger.h"

class Fill : public Color{
    
    public :

        /* Méthodes */
        // Remplissage
        std::string remplissage(const Color& color) const;
        // Contour
        std::string contour(const Color& color) const;

};

#endif // _FILL_H_