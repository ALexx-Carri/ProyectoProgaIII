#include "IndiceInvertido.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

string IndiceInvertido::normalizar(const string& texto) {
    string resultado;
    for(char c : texto) {
        if(isalnum(c)) {
            resultado += tolower(c);
        }
    }
    return resultado;
}

void IndiceInvertido::indexar(const string& termino, int idPelicula) {
    string terminoNormalizado = normalizar(termino);
    if(terminoNormalizado.empty()) return;
    
    auto& lista = indice[terminoNormalizado];
    if(find(lista.begin(), lista.end(), idPelicula) == lista.end()) {
        lista.push_back(idPelicula);
    }
}

void IndiceInvertido::indexarMultiples(const vector<string>& terminos, int idPelicula) {
    for(const string& termino : terminos) {
        indexar(termino, idPelicula);
    }
}

vector<int> IndiceInvertido::buscar(const string& termino) {
    string terminoNormalizado = normalizar(termino);
    if(indice.find(terminoNormalizado) != indice.end()) {
        return indice[terminoNormalizado];
    }
    return {};
}

vector<int> IndiceInvertido::buscarMultiplesOR(const vector<string>& terminos) {
    set<int> resultadoSet;
    
    for(const string& termino : terminos) {
        vector<int> ids = buscar(termino);
        for(int id : ids) {
            resultadoSet.insert(id);
        }
    }
    
    return vector<int>(resultadoSet.begin(), resultadoSet.end());
}

vector<int> IndiceInvertido::buscarMultiplesAND(const vector<string>& terminos) {
    if(terminos.empty()) return {};
    
    vector<int> resultado = buscar(terminos[0]);
    
    for(size_t i = 1; i < terminos.size(); i++) {
        vector<int> actuales = buscar(terminos[i]);
        
        set<int> conjuntoActual(actuales.begin(), actuales.end());
        vector<int> interseccion;
        
        for(int id : resultado) {
            if(conjuntoActual.count(id)) {
                interseccion.push_back(id);
            }
        }
        
        resultado = interseccion;
        if(resultado.empty()) break;
    }
    
    return resultado;
}

void IndiceInvertido::mostrarEstadisticas() {
    cout << "=== ESTADÍSTICAS DEL ÍNDICE INVERTIDO ===" << endl;
    cout << "Términos indexados: " << indice.size() << endl;
    cout << "Estructura: unordered_map<string, vector<int>>" << endl;
    cout << "Complejidad de búsqueda: O(1) promedio" << endl;
}