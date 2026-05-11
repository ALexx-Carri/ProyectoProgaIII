#include <iostream>
#include <vector>

#include "models/Movie.h"

#include "utils/CSVReader.h"
#include "utils/Tokenizar.h"

using namespace std;

void showMenu() {
    cout << endl;
    cout << "======================================" << endl;
    cout << " STREAMING SEARCH ENGINE " << endl;
    cout << "======================================" << endl;
    cout << "1. Leer CSV" << endl;
    cout << "2. Mostrar 5 primeras peliculas" << endl;
    cout << "3. Tokenize peliculas por nombre" << endl;
    cout << "0. Exit" << endl;
    cout << "======================================" << endl;
    cout << "Option: ";
}

int main() {
    vector<Movie> movies;
    CSVReader csvReader;
    Tokenizer tokenizer;
    int option;
    
    do {
        showMenu();
        cin >> option;
        cin.ignore();

        switch(option) {
            case 1: {
                movies = csvReader.loadCSV("dataCleaner.csv");
                cout << endl;
                cout << "Movies loaded: " << movies.size() << endl;
                break;
            }

            case 2: {
                if(movies.empty()) {
                    cout << "Load CSV first" << endl;
                    break;
                }

                for(int i = 0; i < 5 && i < movies.size(); i++) {
                    movies[i].displayMovie();
                }
                break;
            }

            case 3: {
                if(movies.empty()) {
                    cout << "Load CSV first" << endl;
                    break;
                }
                string title = movies[0].getTitle();
                vector<string> tokens = tokenizer.tokenize(title);

                cout << endl;
                cout << "Tokens:" << endl;

                for(string word : tokens) cout << word << endl;
                break;
            }

            case 0: {
                cout << "Exiting..." << endl;
                break;
            }

            default:
                cout << "Invalid option" << endl;
        }

    } while(option != 0);

    return 0;
}