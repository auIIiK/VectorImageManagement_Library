#include "../include/Fill.h"

#include <iostream>
#include <string>

using namespace std;

/* Méthodes */
// Remplissage
string Fill::remplissage(const Color& color) const {

    std::string colorStr = color.RGBAtoString();

    return "fill=\"rgb(" + colorStr + ")\"";
    
}
// Contour
string Fill::contour(const Color& color) const {

    std::string colorStr = color.RGBAtoString();

    return "stroke=\"rgb(" + colorStr + ")\"";
    
}
