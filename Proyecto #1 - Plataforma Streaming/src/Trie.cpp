#include "Trie.h"
#include <iostream>
#include <cctype>

using namespace std;

// ==================== TrieNode ====================
TrieNode::TrieNode() : esFinPalabra(false) {}

TrieNode::~TrieNode() {
    for(auto& par : hijos) {
        delete par.second;
    }
}

// ==================== Trie ====================
Trie::Trie() {
    raiz = new TrieNode();
}

Trie::~Trie() {
    delete raiz;
}

string Trie::limpiarPalabra(const string& palabra) {
    string resultado;
    for(char c : palabra) {
        if(isalnum(c)) {
            resultado += tolower(c);
        }
    }
    return resultado;
}

void Trie::insertar(const string& palabra, int idPelicula) {
    string palabraLimpia = limpiarPalabra(palabra);
    if(palabraLimpia.empty()) return;
    
    TrieNode* actual = raiz;
    
    for(char c : palabraLimpia) {
        if(actual->hijos.find(c) == actual->hijos.end()) {
            actual->hijos[c] = new TrieNode();
        }
        actual = actual->hijos[c];
        actual->idsPeliculas.insert(idPelicula);
    }
    actual->esFinPalabra = true;
}

void Trie::insertarConPrefijos(const string& palabra, int idPelicula) {
    string palabraLimpia = limpiarPalabra(palabra);
    if(palabraLimpia.empty()) return;
    
    // Insertar todos los prefijos posibles (para búsqueda por subpalabra)
    for(size_t i = 1; i <= palabraLimpia.length(); i++) {
        string prefijo = palabraLimpia.substr(0, i);
        
        TrieNode* actual = raiz;
        for(char c : prefijo) {
            if(actual->hijos.find(c) == actual->hijos.end()) {
                actual->hijos[c] = new TrieNode();
            }
            actual = actual->hijos[c];
            actual->idsPeliculas.insert(idPelicula);
        }
    }
}

vector<int> Trie::buscar(const string& consulta) {
    string consultaLimpia = limpiarPalabra(consulta);
    if(consultaLimpia.empty()) return {};
    
    TrieNode* actual = raiz;
    for(char c : consultaLimpia) {
        if(actual->hijos.find(c) == actual->hijos.end()) {
            return {};
        }
        actual = actual->hijos[c];
    }
    
    vector<int> resultado(actual->idsPeliculas.begin(), actual->idsPeliculas.end());
    return resultado;
}

vector<int> Trie::buscarMultiples(const vector<string>& palabras) {
    if(palabras.empty()) return {};
    
    vector<int> resultado = buscar(palabras[0]);
    
    for(size_t i = 1; i < palabras.size(); i++) {
        vector<int> actuales = buscar(palabras[i]);
        
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

void Trie::mostrarEstadisticas() {
    cout << "=== ESTADÍSTICAS DEL TRIE (ÁRBOL) ===" << endl;
    cout << "Estructura: Árbol donde cada nodo contiene un carácter" << endl;
    cout << "Complejidad de búsqueda: O(k) donde k = longitud de la palabra" << endl;
    cout << "Permite búsqueda por subpalabras y prefijos" << endl;
}