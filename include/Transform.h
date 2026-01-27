#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Color.h"
#include "Logger.h"

class Transform{

    public :
    
        /* Méthodes virtuelles pures */
        // Translation
        virtual void translation(const int x, const int y) = 0;
        // Rotation
        virtual void rotation(const int angle) = 0;
        // Scaling
        virtual void scaling(const double scaleFactor) = 0;
        // Remplissage
        virtual void fill(const Color color) = 0;
        // Contour
        virtual void contour(const Color color) = 0;

};

#endif // _TRANSFORM_H_