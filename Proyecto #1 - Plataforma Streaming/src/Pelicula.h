#ifndef PELICULA_H
#define PELICULA_H

#include <string>
#include <vector>

using namespace std;

struct Pelicula {
    int id = -1;
    int releaseYear = 0;
    string title = "";
    string originEthnicity = "";
    string director = "Unknown";
    string cast = "Unknown";
    string genre = "";
    string wikiPage = "";
    string plot = "";
    
    // Metadatos para el ranking
    int likes = 0;
    bool verMasTarde = false;
    int vecesBuscada = 0;
};

#endif