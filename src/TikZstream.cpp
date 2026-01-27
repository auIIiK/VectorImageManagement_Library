#include "../include/TikZstream.h"

using namespace std;

//Fermeture
void TikZstream::close(){
    Logger::log("Fermeture du TikZstream");
    if(this->fileStream.is_open()){
        this->fileStream << "\\end{tikzpicture}" << std::endl;
        this->fileStream << "\\end{document}" << std::endl;
        this->fileStream.close();
    }
}

//Constructeur
TikZstream::TikZstream(const std::string &filename, const double height, const double width, Color colorFond){
    Logger::log("Constructeur du TikZstream");
    this->filename = filename;
    this->height = height;
    this->width = width;
    this->colorFond = colorFond;

    this->fileStream.open(this->filename);

    if(!this->fileStream){
        cerr << "Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

    this->fileStream << "\\documentclass{standalone}" << std::endl;
    this->fileStream << "\\usepackage{tikz}" << std::endl;
    this->fileStream << "\\begin{document}" << std::endl;
    this->fileStream << "\\begin{tikzpicture}" << std::endl;
}

//Destructeur
TikZstream::~TikZstream(){
    Logger::log("Destructeur du TikZstream");
    if(this->fileStream.is_open()){
        this->fileStream << "\n\\end{tikzpicture}" << std::endl;
        this->fileStream << "\\end{document}" << std::endl;
        this->fileStream.close();
    }
}

//Ouverture
bool TikZstream::open(const std::string &filename){
    Logger::log("Ouverture du TikZstream");
    this->filename = filename;
    this->fileStream.open(this->filename);
    if(this->fileStream.is_open()){
        this->fileStream << "\\documentclass{standalone}" << std::endl;
        this->fileStream << "\\usepackage{tikz}" << std::endl;
        this->fileStream << "\\begin{document}" << std::endl;
        this->fileStream << "\\begin{tikzpicture}" << std::endl;
        this->fileStream << "\\draw[fill= RGBA(" << this->colorFond.RGBAtoString() << ")] (0,0) rectangle (" << this->width << "," << this->height << ");" << std::endl;
        return true;
    }
    return false;
}

//Surchage de l'opérateur <<
TikZstream& operator<<(TikZstream& stream, const char *str){
    stream.fileStream << str;
    return stream;
}

TikZstream& operator<<(TikZstream& stream, float val){
    stream.fileStream << val;
    return stream;
}

TikZstream& operator<<(TikZstream& stream, std::string str){
    stream.fileStream << str;
    return stream;
}

