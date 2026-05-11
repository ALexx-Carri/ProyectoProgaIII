#include "Tokenizar.h"

#include <cctype>

using namespace std;

vector<string> Tokenizer::tokenize(string text) {

    vector<string> words;

    string currentWord;

    for(char c : text) {

        if(isalnum(c)) {

            currentWord += tolower(c);
        }
        else {

            if(!currentWord.empty()) {

                words.push_back(currentWord);

                currentWord.clear();
            }
        }
    }

    if(!currentWord.empty()) {

        words.push_back(currentWord);
    }

    return words;
}