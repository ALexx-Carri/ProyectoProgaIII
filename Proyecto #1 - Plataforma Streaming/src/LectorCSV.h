#ifndef LECTORCSV_H
#define LECTORCSV_H

#include <vector>
#include <string>
#include "Pelicula.h"

using namespace std;

vector<string> splitCSV(const string& linea);
vector<string> split(const string& str, char delim);
vector<Pelicula> leerCSV(const string& archivo);

#endif