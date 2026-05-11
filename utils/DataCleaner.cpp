#include "DataCleaner.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

string DataCleaner::limpiarTexto(const string& texto) {
    string resultado;
    // Eliminar caracteres extraños y convertir a minúsculas
    for (char c : texto) {
        if (c == '\r' || c == '\n' || c == '\t') {
            continue;
        }
        resultado += tolower(c);
    }

    // Eliminar espacios innecesarios al inicio y final
    while (!resultado.empty() && resultado.front() == ' ') {
        resultado.erase(resultado.begin());
    }
    while (!resultado.empty() && resultado.back() == ' ') {
        resultado.pop_back();
    }
    return resultado;
}

vector<string> DataCleaner::separarCSV(const string& linea) {
    vector<string> columnas;
    string valor;
    bool dentroComillas = false;

    for (char c : linea) {
        if (c == '"') {
            dentroComillas = !dentroComillas;
        }
        else if (c == ',' && !dentroComillas) {
            columnas.push_back(valor);
            valor.clear();
        }
        else valor += c;
    }

    columnas.push_back(valor);
    return columnas;
}

bool DataCleaner::esFilaValida(const vector<string>& columnas) {
    if (columnas.size() < 8) return false;
    if (columnas[1].empty()) return false;
    if (columnas[7].empty()) return false;

    return true;
}

string DataCleaner::generarClaveUnica(const string& titulo,const string& año) {
    return titulo + "_" + año;
}

void DataCleaner::limpiarCSV(const string& archivoEntrada, const string& archivoSalida) {

    ifstream archivoOriginal(archivoEntrada);
    ofstream archivoLimpio(archivoSalida);

    if (!archivoOriginal.is_open()) {
        cout << "Error al abrir archivo de entrada" << endl;
        return;
    }

    if (!archivoLimpio.is_open()) {
        cout << "Error al crear archivo limpio" << endl;
        return;
    }

    string linea;
    bool primeraLinea = true;

    string lineaCompleta;
    int contadorComillas = 0;

    while (getline(archivoOriginal, linea)) {

        // Mantener header
        if (primeraLinea) {
            archivoLimpio << linea << endl;
            primeraLinea = false;
            continue;
        }

        lineaCompleta += linea;

        contadorComillas += count(linea.begin(), linea.end(), '"');

        // Si las comillas son pares, el registro está completo
        if (contadorComillas % 2 == 0) {

            vector<string> columnas = separarCSV(lineaCompleta);

            if (!esFilaValida(columnas)) {
                lineaCompleta.clear();
                contadorComillas = 0;
                continue;
            }

            for (string& columna : columnas) {
                columna = limpiarTexto(columna);

                if (columna.empty()) {
                    columna = "unknown";
                }
            }

            string año = columnas[0];
            string titulo = columnas[1];

            // Eliminar duplicados
            string clave = generarClaveUnica(titulo, año);

            if (peliculasUnicas.count(clave)) {
                lineaCompleta.clear();
                contadorComillas = 0;
                continue;
            }

            peliculasUnicas.insert(clave);

            // Escribir fila limpia
            for (int i = 0; i < columnas.size(); i++) {
                archivoLimpio << "\"" << columnas[i] << "\"";

                if (i != columnas.size() - 1) {
                    archivoLimpio << ",";
                }
            }

            archivoLimpio << endl;

            // Reiniciar acumuladores
            lineaCompleta.clear();
            contadorComillas = 0;
        }
        else {
            // Sigue leyendo porque el registro continúa
            lineaCompleta += " ";
        }
    }

    archivoOriginal.close();
    archivoLimpio.close();

    cout << "Limpieza finalizada correctamente" << endl;
}