#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* Classe pour sortir tout les print facultatif dans un fichier log */
class Logger
{
  public:
    static void log(const string &message){
        ofstream file;
        file.open("log/debug.txt", ios::app);
        file << message << endl;
        file.close();
    }

};

#endif // LOGGER_H