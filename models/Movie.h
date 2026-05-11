#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

using namespace std;

class Movie {
    int id, releaseYear;
    string title, originEthnicity, director;

    vector<string> cast;
    vector<string> genres;

    string wikiPage, plot;
    int likes, searchCount;

public:
    Movie();

    Movie(int id, int releaseYear, string title, string originEthnicity, string director, vector<string> cast,
        vector<string> genres,
        string wikiPage,
        string plot
    );

    // Getters
    int getId() const;

    int getReleaseYear() const;

    string getTitle() const;

    string getDirector() const;

    string getPlot() const;

    vector<string> getGenres() const;

    vector<string> getCast() const;

    // Ranking
    int getLikes() const;

    int getSearchCount() const;

    void addLike();

    void increaseSearchCount();

    // Mostrar información
    void displayMovie() const;
};

#endif