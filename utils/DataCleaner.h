#ifndef NEW_PROYECT_DATACLEANER_H
#define NEW_PROYECT_DATACLEANER_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class DataCleaner {

    unordered_set<string> peliculasUnicas;
    vector<string> separarCSV(const string& linea);

    bool esFilaValida(const vector<string>& columnas);

    string limpiarTexto(const string& texto);
    string generarClaveUnica(const string& titulo,const string& Año);

public:
    void limpiarCSV(const string& archivoEntrada, const string& archivoSalida);
};

#endif