#include "LectorCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

using namespace std;

vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while(getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> splitCSV(const string& linea) {
    vector<string> campos;
    string campo;
    bool dentroComillas = false;
    
    for(size_t i = 0; i < linea.length(); i++) {
        char c = linea[i];
        
        if(c == '"') {
            dentroComillas = !dentroComillas;
        }
        else if(c == ',' && !dentroComillas) {
            campos.push_back(campo);
            campo.clear();
        }
        else {
            campo += c;
        }
    }
    campos.push_back(campo);
    
    // Limpiar espacios en blanco al inicio y final de cada campo
    for(string& c : campos) {
        // Eliminar espacios al inicio
        while(!c.empty() && isspace(c.front())) {
            c.erase(0, 1);
        }
        // Eliminar espacios al final
        while(!c.empty() && isspace(c.back())) {
            c.pop_back();
        }
    }
    
    return campos;
}

// Función auxiliar para convertir string a int de forma segura
int toIntSafe(const string& str) {
    if(str.empty()) return 0;
    
    // Verificar si todos los caracteres son dígitos
    for(char c : str) {
        if(!isdigit(c)) {
            return 0;
        }
    }
    
    try {
        return stoi(str);
    } catch(...) {
        return 0;
    }
}

vector<Pelicula> leerCSV(const string& archivo) {
    vector<Pelicula> peliculas;
    ifstream file(archivo);
    
    if(!file.is_open()) {
        cout << "Error: No se pudo abrir " << archivo << endl;
        return peliculas;
    }
    
    string linea;
    // Saltar cabecera
    getline(file, linea);
    
    int id = 0;
    int lineasLeidas = 0;
    int errores = 0;
    
    while(getline(file, linea)) {
        lineasLeidas++;
        vector<string> campos = splitCSV(linea);
        
        // Verificar que tenga al menos 8 campos
        if(campos.size() < 8) {
            errores++;
            continue;
        }
        
        Pelicula p;
        p.id = id++;
        
        // Año - convertir de forma segura
        p.releaseYear = toIntSafe(campos[0]);
        
        // Título
        p.title = campos[1];
        if(p.title.empty()) p.title = "Sin título";
        
        // Origen
        p.originEthnicity = campos[2];
        
        // Director
        p.director = campos[3];
        if(p.director.empty()) p.director = "Unknown";
        
        // Cast
        p.cast = campos[4];
        if(p.cast.empty()) p.cast = "Unknown";
        
        // Género
        p.genre = campos[5];
        
        // Wiki Page
        p.wikiPage = (campos.size() > 6) ? campos[6] : "";
        
        // Plot (sinopsis)
        p.plot = (campos.size() > 7) ? campos[7] : "";
        
        // Limpiar comillas del plot si existen
        if(!p.plot.empty() && p.plot.front() == '"') {
            p.plot = p.plot.substr(1, p.plot.length() - 2);
        }
        
        // Limpiar caracteres especiales del plot
        string plotLimpio;
        for(char c : p.plot) {
            if(isprint(c) || c == ' ' || c == '\n') {
                plotLimpio += c;
            }
        }
        p.plot = plotLimpio;
        
        // Inicializar metadatos
        p.likes = 0;
        p.verMasTarde = false;
        p.vecesBuscada = 0;
        
        peliculas.push_back(p);
        
        if(id % 1000 == 0) {
            cout << "Cargadas " << id << " películas..." << endl;
        }
    }
    
    file.close();
    cout << "✅ Total cargadas: " << peliculas.size() << " películas" << endl;
    if(errores > 0) {
        cout << "⚠️ Líneas omitidas por error: " << errores << endl;
    }
    return peliculas;
}