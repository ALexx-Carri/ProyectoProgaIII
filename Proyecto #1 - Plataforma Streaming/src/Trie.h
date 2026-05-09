#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <set>
#include <string>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> hijos;
    set<int> idsPeliculas;  // IDs de películas que pasan por este nodo
    bool esFinPalabra;
    
    TrieNode();
    ~TrieNode();
};

class Trie {
private:
    TrieNode* raiz;
    string limpiarPalabra(const string& palabra);
    
public:
    Trie();
    ~Trie();
    
    void insertar(const string& palabra, int idPelicula);
    void insertarConPrefijos(const string& palabra, int idPelicula);
    vector<int> buscar(const string& consulta);
    vector<int> buscarMultiples(const vector<string>& palabras);
    void mostrarEstadisticas();
};

#endif