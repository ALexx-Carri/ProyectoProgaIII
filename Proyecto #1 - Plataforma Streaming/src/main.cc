#include "Plataforma.h"
#include <iostream>
#include <limits>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void mostrarMenu() {
    cout << "\n╔══════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    PLATAFORMA DE STREAMING                           ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  1. Buscar película (título/sinopsis)                                ║" << endl;
    cout << "║  2. Buscar por género                                                ║" << endl;
    cout << "║  3. Buscar por director                                              ║" << endl;
    cout << "║  4. Búsqueda combinada (texto + género)                              ║" << endl;
    cout << "║  5. Ver 'Ver más tarde'                                              ║" << endl;
    cout << "║  6. Ver recomendaciones                                              ║" << endl;
    cout << "║  7. Mostrar estadísticas de estructuras                              ║" << endl;
    cout << "║  0. Salir                                                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════╝" << endl;
    cout << "Opción: ";
}

int main() {
    // Configurar consola para UTF-8 en Windows
    SetConsoleOutputCP(CP_UTF8);    
    Plataforma plataforma;
    
    cout << "\n Cargando base de datos..." << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    if(!plataforma.cargarCSV("wiki_movie_plots_deduped.csv")) {
        cout << "No se pudo cargar el archivo." << endl;
        cout << "Asegúrate de que 'wiki_movie_plots_deduped.csv' está en la misma carpeta." << endl;
        return 1;
    }
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(opcion) {
            case 1: {
                string consulta;
                cout << "\n Buscar: ";
                getline(cin, consulta);
                
                vector<int> resultados = plataforma.buscarGeneral(consulta);
                vector<string> palabras = {}; // Se extraerán dentro de mostrarResultadosPaginados
                
                // Extraer palabras de la consulta para el ranking
                string temp = consulta;
                vector<string> palabrasBuscadas;
                string palabraActual;
                for(char c : temp) {
                    if(isalnum(c)) {
                        palabraActual += tolower(c);
                    } else if(!palabraActual.empty()) {
                        if(palabraActual.length() > 2) {
                            palabrasBuscadas.push_back(palabraActual);
                        }
                        palabraActual.clear();
                    }
                }
                if(!palabraActual.empty() && palabraActual.length() > 2) {
                    palabrasBuscadas.push_back(palabraActual);
                }
                
                plataforma.mostrarResultadosPaginados(resultados, palabrasBuscadas);
                break;
            }
            case 2: {
                string genero;
                cout << "\n Género: ";
                getline(cin, genero);
                
                vector<int> resultados = plataforma.buscarPorGenero(genero);
                vector<string> vacio;
                plataforma.mostrarResultadosPaginados(resultados, vacio);
                break;
            }
            case 3: {
                string director;
                cout << "\n Director: ";
                getline(cin, director);
                
                vector<int> resultados = plataforma.buscarPorDirector(director);
                vector<string> vacio;
                plataforma.mostrarResultadosPaginados(resultados, vacio);
                break;
            }
            case 4: {
                string texto, genero;
                cout << "\n Texto a buscar: ";
                getline(cin, texto);
                cout << " Género: ";
                getline(cin, genero);
                
                vector<int> resultados = plataforma.buscarCombinado(texto, genero);
                
                // Extraer palabras para ranking
                vector<string> palabrasBuscadas;
                string palabraActual;
                for(char c : texto) {
                    if(isalnum(c)) {
                        palabraActual += tolower(c);
                    } else if(!palabraActual.empty()) {
                        if(palabraActual.length() > 2) {
                            palabrasBuscadas.push_back(palabraActual);
                        }
                        palabraActual.clear();
                    }
                }
                if(!palabraActual.empty() && palabraActual.length() > 2) {
                    palabrasBuscadas.push_back(palabraActual);
                }
                
                plataforma.mostrarResultadosPaginados(resultados, palabrasBuscadas);
                break;
            }
            case 5:
                plataforma.mostrarVerMasTarde();
                break;
            case 6:
                plataforma.recomendarPorLikes();
                break;
            case 7:
                plataforma.mostrarEstadisticas();
                break;
            case 0:
                cout << "\n ¡Hasta luego!" << endl;
                break;
            default:
                cout << "\n Opción no válida" << endl;
        }
    } while(opcion != 0);
    
    return 0;
}
