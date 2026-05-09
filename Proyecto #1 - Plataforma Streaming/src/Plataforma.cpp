#include "Plataforma.h"
#include "LectorCSV.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <set>
#include <limits>

using namespace std;

// ==================== CONSTRUCTOR ====================
// No hay constructor explícito, pero podemos inicializar en cargarCSV

// ==================== MÉTODOS PRIVADOS AUXILIARES ====================

vector<string> Plataforma::extraerPalabras(const string& texto) {
    vector<string> palabras;
    string palabraActual;
    
    for(char c : texto) {
        if(isalnum(c)) {
            palabraActual += tolower(c);
        } else if(!palabraActual.empty()) {
            if(palabraActual.length() > 2) {
                palabras.push_back(palabraActual);
            }
            palabraActual.clear();
        }
    }
    
    if(!palabraActual.empty() && palabraActual.length() > 2) {
        palabras.push_back(palabraActual);
    }
    
    return palabras;
}

float Plataforma::calcularImportancia(int idPelicula, const vector<string>& palabrasBuscadas) {
    if(idPelicula < 0 || idPelicula >= (int)peliculas.size()) return 0.0f;
    
    const Pelicula& p = peliculas[idPelicula];
    float puntaje = 0.0f;
    
    // Factor 1: Veces buscada (popularidad)
    puntaje += p.vecesBuscada * 0.5f;
    
    // Factor 2: Likes del usuario
    puntaje += p.likes * 2.0f;
    
    // Factor 3: Relevancia en título (mayor peso)
    string tituloLower = p.title;
    for(char& c : tituloLower) c = tolower(c);
    
    for(const string& palabra : palabrasBuscadas) {
        if(tituloLower.find(palabra) != string::npos) {
            puntaje += 10.0f;
        }
        
        string plotLower = p.plot;
        for(char& c : plotLower) c = tolower(c);
        if(plotLower.find(palabra) != string::npos) {
            puntaje += 3.0f;
        }
    }
    
    // Factor 4: Año (películas más recientes)
    if(p.releaseYear > 2000) puntaje += 1.0f;
    if(p.releaseYear > 2010) puntaje += 1.0f;
    
    // Factor 5: Director conocido
    if(p.director != "Unknown" && p.director != "") {
        puntaje += 2.0f;
    }
    
    return puntaje;
}

void Plataforma::indexarPelicula(const Pelicula& p) {
    // Indexar título en el Trie
    vector<string> palabrasTitulo = extraerPalabras(p.title);
    for(const string& palabra : palabrasTitulo) {
        arbolTrie.insertarConPrefijos(palabra, p.id);
    }
    
    // Indexar sinopsis en el Trie
    vector<string> palabrasPlot = extraerPalabras(p.plot);
    for(const string& palabra : palabrasPlot) {
        arbolTrie.insertarConPrefijos(palabra, p.id);
    }
    
    // Indexar director en índice invertido
    if(p.director != "Unknown" && p.director != "") {
        indiceDirector.indexar(p.director, p.id);
    }
    
    // Indexar género
    if(p.genre != "") {
        vector<string> generos = split(p.genre, ',');
        for(string& g : generos) {
            while(!g.empty() && g.front() == ' ') g.erase(0, 1);
            while(!g.empty() && g.back() == ' ') g.pop_back();
            if(!g.empty()) {
                indiceGenero.indexar(g, p.id);
            }
        }
    }
    
    // Indexar actores (primeros 3)
    if(p.cast != "" && p.cast != "Unknown") {
        vector<string> actores = split(p.cast, ',');
        for(size_t i = 0; i < min(actores.size(), size_t(3)); i++) {
            string actor = actores[i];
            while(!actor.empty() && actor.front() == ' ') actor.erase(0, 1);
            if(!actor.empty()) {
                indiceActores.indexar(actor, p.id);
            }
        }
    }
}

// ==================== MÉTODOS PÚBLICOS ====================

bool Plataforma::cargarCSV(const string& archivo) {
    peliculas = leerCSV(archivo);
    
    if(peliculas.empty()) {
        return false;
    }
    
    // Indexar cada película
    for(const Pelicula& p : peliculas) {
        indexarPelicula(p);
    }
    
    cout << "✅ Indexación completada para " << peliculas.size() << " películas" << endl;
    return true;
}

vector<int> Plataforma::buscarGeneral(const string& consulta) {
    vector<string> palabras = extraerPalabras(consulta);
    
    if(palabras.empty()) return {};
    
    if(palabras.size() == 1) {
        return arbolTrie.buscar(palabras[0]);
    }
    
    return arbolTrie.buscarMultiples(palabras);
}

vector<int> Plataforma::buscarPorGenero(const string& genero) {
    return indiceGenero.buscar(genero);
}

vector<int> Plataforma::buscarPorDirector(const string& director) {
    return indiceDirector.buscar(director);
}

vector<int> Plataforma::buscarCombinado(const string& texto, const string& genero) {
    vector<int> idsPorTexto = buscarGeneral(texto);
    vector<int> idsPorGenero = indiceGenero.buscar(genero);
    
    set<int> setGenero(idsPorGenero.begin(), idsPorGenero.end());
    vector<int> resultado;
    
    for(int id : idsPorTexto) {
        if(setGenero.count(id)) {
            resultado.push_back(id);
        }
    }
    
    return resultado;
}

vector<int> Plataforma::obtenerTopImportantes(const vector<int>& ids, 
                                                const vector<string>& palabrasBuscadas,
                                                int cantidad) {
    vector<pair<int, float>> idsConPuntaje;
    
    for(int id : ids) {
        if(id >= 0 && id < (int)peliculas.size()) {
            float puntaje = calcularImportancia(id, palabrasBuscadas);
            idsConPuntaje.push_back({id, puntaje});
        }
    }
    
    sort(idsConPuntaje.begin(), idsConPuntaje.end(),
         [](const pair<int,float>& a, const pair<int,float>& b) {
             return a.second > b.second;
         });
    
    vector<int> top;
    for(int i = 0; i < min(cantidad, (int)idsConPuntaje.size()); i++) {
        top.push_back(idsConPuntaje[i].first);
        peliculas[idsConPuntaje[i].first].vecesBuscada++;
    }
    
    return top;
}

void Plataforma::mostrarResultadosPaginados(const vector<int>& ids, 
                                             const vector<string>& palabrasBuscadas) {
    if(ids.empty()) {
        cout << "\n❌ No se encontraron resultados" << endl;
        return;
    }
    
    vector<int> top = obtenerTopImportantes(ids, palabrasBuscadas, ids.size());
    
    int pagina = 0;
    int porPagina = 5;
    int totalPaginas = (top.size() + porPagina - 1) / porPagina;
    
    while(true) {
        cout << "\n📄 Página " << (pagina + 1) << " de " << totalPaginas << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        
        int inicio = pagina * porPagina;
        int fin = min(inicio + porPagina, (int)top.size());
        
        for(int i = inicio; i < fin; i++) {
            int id = top[i];
            const Pelicula& p = peliculas[id];
            cout << (i + 1) << ". 🎬 " << p.title << " (" << p.releaseYear << ")" << endl;
            cout << "   Director: " << p.director << endl;
            cout << "   Género: " << (p.genre.empty() ? "No especificado" : p.genre) << endl;
            cout << "   🔍 Popularidad: " << p.vecesBuscada << " búsquedas" << endl;
            cout << "   ❤️ Likes: " << p.likes << endl;
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        }
        
        cout << "[N] Siguiente  [P] Anterior  [V] Ver detalles  [0] Salir" << endl;
        cout << "Opción: ";
        
        char opcion;
        cin >> opcion;
        cin.ignore();
        
        if(opcion == 'N' || opcion == 'n') {
            if(pagina + 1 < totalPaginas) pagina++;
            else cout << "📌 Última página" << endl;
        }
        else if(opcion == 'P' || opcion == 'p') {
            if(pagina > 0) pagina--;
            else cout << "📌 Primera página" << endl;
        }
        else if(opcion == 'V' || opcion == 'v') {
            int seleccion;
            cout << "Número de película: ";
            cin >> seleccion;
            cin.ignore();
            
            if(seleccion >= inicio + 1 && seleccion <= fin) {
                verDetallePelicula(top[seleccion - 1]);
            } else {
                cout << "❌ Selección no válida" << endl;
            }
        }
        else if(opcion == '0') {
            break;
        }
    }
}

void Plataforma::verDetallePelicula(int id) {
    if(id < 0 || id >= (int)peliculas.size()) return;
    
    Pelicula& p = peliculas[id];
    
    cout << "\n╔══════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  🎬 " << p.title << " (" << p.releaseYear << ")" << endl;
    cout << "╠══════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  📍 Origen: " << p.originEthnicity << endl;
    cout << "║  🎭 Director: " << p.director << endl;
    cout << "║  👥 Reparto: " << p.cast << endl;
    cout << "║  🏷️  Género: " << (p.genre.empty() ? "No especificado" : p.genre) << endl;
    cout << "║  📖 Sinopsis: " << endl;
    
    // Mostrar sinopsis con formato (80 caracteres por línea)
    string plot = p.plot;
    size_t pos = 0;
    while(pos < plot.length()) {
        size_t end = plot.find(' ', pos + 80);
        if(end == string::npos) end = plot.length();
        cout << "║     " << plot.substr(pos, end - pos) << endl;
        pos = end + 1;
    }
    
    cout << "╠══════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  ❤️ Likes: " << p.likes << "  |  🔍 Búsquedas: " << p.vecesBuscada << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n[1] 👍 Dar Like    [2] 📌 Ver más tarde    [0] Volver" << endl;
    cout << "Opción: ";
    
    int opcion;
    cin >> opcion;
    cin.ignore();
    
    if(opcion == 1) {
        darLike(id);
    }
    else if(opcion == 2) {
        anadirVerMasTarde(id);
    }
}

void Plataforma::darLike(int id) {
    if(id >= 0 && id < (int)peliculas.size()) {
        peliculas[id].likes++;
        cout << "✅ ¡Like añadido a " << peliculas[id].title << "!" << endl;
    }
}

void Plataforma::anadirVerMasTarde(int id) {
    if(id >= 0 && id < (int)peliculas.size()) {
        peliculas[id].verMasTarde = true;
        cout << "✅ Añadido a 'Ver más tarde': " << peliculas[id].title << endl;
    }
}

void Plataforma::mostrarVerMasTarde() {
    cout << "\n=== 📌 MIS PELÍCULAS PARA VER MÁS TARDE ===" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    bool encontrada = false;
    for(Pelicula& p : peliculas) {
        if(p.verMasTarde) {
            cout << "🎬 " << p.title << " (" << p.releaseYear << ")" << endl;
            cout << "   Director: " << p.director << endl;
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
            encontrada = true;
        }
    }
    
    if(!encontrada) {
        cout << "No hay películas en 'Ver más tarde'" << endl;
    }
}

void Plataforma::recomendarPorLikes() {
    set<string> generosLiked;
    set<string> directoresLiked;
    
    // Recoger preferencias de películas con like
    for(Pelicula& p : peliculas) {
        if(p.likes > 0) {
            if(p.genre != "") {
                vector<string> generos = split(p.genre, ',');
                for(string& g : generos) {
                    while(!g.empty() && g.front() == ' ') g.erase(0, 1);
                    generosLiked.insert(g);
                }
            }
            if(p.director != "Unknown" && p.director != "") {
                directoresLiked.insert(p.director);
            }
        }
    }
    
    if(generosLiked.empty() && directoresLiked.empty()) {
        cout << "\n❌ Da like a algunas películas para obtener recomendaciones" << endl;
        return;
    }
    
    set<int> idsRecomendados;
    
    for(const string& genero : generosLiked) {
        vector<int> ids = indiceGenero.buscar(genero);
        for(int id : ids) {
            if(peliculas[id].likes == 0) {
                idsRecomendados.insert(id);
            }
        }
    }
    
    for(const string& director : directoresLiked) {
        vector<int> ids = indiceDirector.buscar(director);
        for(int id : ids) {
            if(peliculas[id].likes == 0) {
                idsRecomendados.insert(id);
            }
        }
    }
    
    vector<int> recomendados(idsRecomendados.begin(), idsRecomendados.end());
    vector<string> palabrasVacias;
    vector<int> top = obtenerTopImportantes(recomendados, palabrasVacias, 5);
    
    cout << "\n=== 🎯 RECOMENDACIONES PARA TI ===" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    if(top.empty()) {
        cout << "No hay recomendaciones disponibles" << endl;
    } else {
        for(int id : top) {
            cout << "🎬 " << peliculas[id].title << " (" << peliculas[id].releaseYear << ")" << endl;
            cout << "   Director: " << peliculas[id].director << endl;
            cout << "   Género: " << peliculas[id].genre << endl;
            cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        }
    }
}

void Plataforma::mostrarEstadisticas() {
    cout << "\n╔══════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    ESTRUCTURAS DE DATOS IMPLEMENTADAS                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════╝" << endl;
    
    arbolTrie.mostrarEstadisticas();
    cout << endl;
    indiceGenero.mostrarEstadisticas();
    
    cout << "\n📊 Total de películas indexadas: " << peliculas.size() << endl;
}