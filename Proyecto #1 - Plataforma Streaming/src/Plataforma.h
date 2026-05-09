#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <vector>
#include <string>
#include "Pelicula.h"
#include "Trie.h"
#include "IndiceInvertido.h"

using namespace std;

class Plataforma {
private:
    vector<Pelicula> peliculas;
    Trie arbolTrie;
    IndiceInvertido indiceGenero;
    IndiceInvertido indiceDirector;
    IndiceInvertido indiceActores;
    
    // Métodos privados auxiliares
    vector<string> extraerPalabras(const string& texto);
    float calcularImportancia(int idPelicula, const vector<string>& palabrasBuscadas);
    void indexarPelicula(const Pelicula& p);
    
public:
    bool cargarCSV(const string& archivo);
    
    // Búsquedas
    vector<int> buscarGeneral(const string& consulta);
    vector<int> buscarPorGenero(const string& genero);
    vector<int> buscarPorDirector(const string& director);
    vector<int> buscarCombinado(const string& texto, const string& genero);
    
    // Ranking y resultados
    vector<int> obtenerTopImportantes(const vector<int>& ids, 
                                       const vector<string>& palabrasBuscadas,
                                       int cantidad = 5);
    void mostrarResultadosPaginados(const vector<int>& ids, 
                                     const vector<string>& palabrasBuscadas);
    void verDetallePelicula(int id);
    
    // Acciones del usuario
    void darLike(int id);
    void anadirVerMasTarde(int id);
    void mostrarVerMasTarde();
    void recomendarPorLikes();
    void mostrarEstadisticas();
    
    // Getters
    const vector<Pelicula>& getPeliculas() const { return peliculas; }
};

#endif