#include "CSVReader.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> CSVReader::splitCSVLine(string line) {

    vector<string> columns;

    string value;

    bool insideQuotes = false;

    for(char c : line) {

        if(c == '"') {

            insideQuotes = !insideQuotes;
        }
        else if(c == ',' && !insideQuotes) {

            columns.push_back(value);

            value.clear();
        }
        else {

            value += c;
        }
    }

    columns.push_back(value);

    return columns;
}

vector<string> CSVReader::splitByComma(string text) {

    vector<string> result;

    stringstream ss(text);

    string item;

    while(getline(ss, item, ',')) {

        result.push_back(item);
    }

    return result;
}

vector<Movie> CSVReader::loadCSV(string filePath) {

    vector<Movie> movies;

    ifstream file(filePath);

    if(!file.is_open()) {

        cout << "Error opening CSV file" << endl;

        return movies;
    }

    string line;

    getline(file, line);

    int id = 0;

    while(getline(file, line)) {

        vector<string> columns =
            splitCSVLine(line);

        if(columns.size() < 8) continue;

        int year = 0;

        try {

            year = stoi(columns[0]);
        }
        catch(...) {

            year = 0;
        }

        string title = columns[1];

        string origin = columns[2];

        string director = columns[3];

        vector<string> cast =
            splitByComma(columns[4]);

        vector<string> genres =
            splitByComma(columns[5]);

        string wiki = columns[6];

        string plot = columns[7];

        Movie movie(
            id,
            year,
            title,
            origin,
            director,
            cast,
            genres,
            wiki,
            plot
        );

        movies.push_back(movie);

        id++;
    }

    file.close();

    return movies;
}