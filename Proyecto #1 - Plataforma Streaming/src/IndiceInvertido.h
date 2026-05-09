#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class IndiceInvertido {
private:
    unordered_map<string, vector<int>> indice;
    string normalizar(const string& texto);
    
public:
    void indexar(const string& termino, int idPelicula);
    void indexarMultiples(const vector<string>& terminos, int idPelicula);
    vector<int> buscar(const string& termino);
    vector<int> buscarMultiplesOR(const vector<string>& terminos);
    vector<int> buscarMultiplesAND(const vector<string>& terminos);
    void mostrarEstadisticas();
};

#endif