#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>

#include "../models/Movie.h"

using namespace std;

class CSVReader {

private:

    vector<string> splitCSVLine(string line);

    vector<string> splitByComma(string text);

public:

    vector<Movie> loadCSV(string filePath);
};

#endif