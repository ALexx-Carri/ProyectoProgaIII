#include "Movie.h"

#include <iostream>

using namespace std;

Movie::Movie() {

    id = -1;
    releaseYear = 0;

    likes = 0;
    searchCount = 0;
}

Movie::Movie(
    int id,
    int releaseYear,
    string title,
    string originEthnicity,
    string director,
    vector<string> cast,
    vector<string> genres,
    string wikiPage,
    string plot
) {

    this->id = id;
    this->releaseYear = releaseYear;

    this->title = title;
    this->originEthnicity = originEthnicity;
    this->director = director;

    this->cast = cast;
    this->genres = genres;

    this->wikiPage = wikiPage;
    this->plot = plot;

    likes = 0;
    searchCount = 0;
}

int Movie::getId() const {
    return id;
}

int Movie::getReleaseYear() const {
    return releaseYear;
}

string Movie::getTitle() const {
    return title;
}

string Movie::getDirector() const {
    return director;
}

string Movie::getPlot() const {
    return plot;
}

vector<string> Movie::getGenres() const {
    return genres;
}

vector<string> Movie::getCast() const {
    return cast;
}

int Movie::getLikes() const {
    return likes;
}

int Movie::getSearchCount() const {
    return searchCount;
}

void Movie::addLike() {
    likes++;
}

void Movie::increaseSearchCount() {
    searchCount++;
}

void Movie::displayMovie() const {

    cout << "========================================" << endl;

    cout << "Title: " << title << endl;

    cout << "Year: " << releaseYear << endl;

    cout << "Director: " << director << endl;

    cout << "Plot: " << plot << endl;

    cout << "Likes: " << likes << endl;

    cout << "Searches: " << searchCount << endl;

    cout << "========================================" << endl;
}