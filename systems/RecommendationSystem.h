#ifndef NEW_PROYECT_RECOMMENDATIONSYSTEM_H
#define NEW_PROYECT_RECOMMENDATIONSYSTEM_H


#include "../models/Movie.h"
#include <vector>

using namespace std;

class RecommendationSystem {

public:

    vector<Movie> recommendMovies(
        const vector<Movie>& likedMovies,
        const vector<Movie>& allMovies
    );
};

#endif //NEW_PROYECT_RECOMMENDATIONSYSTEM_H
