//
// Created by ebbew on 20-11-2024.
//

#include <sstream>
#include "MovieOrShow.h"

MovieOrShow::MovieOrShow(MovieOrShow::Type type, int releaseYear, const string &title, string *genre, float imDbRating)
        : type(type), releaseYear(releaseYear), title(title), genre(genre), IMDbRating(imDbRating) {}

const string &MovieOrShow::getTitle() const {
    return title;
}

string *MovieOrShow::getGenre() const {
    return genre;
}

float MovieOrShow::getImDbRating() const {
    return IMDbRating;
}

string MovieOrShow::toString() {
    string s;
    stringstream ss(s);
    ss << title << "[ genre: " << genre << " IDMb: " << IMDbRating << " ]";
    return s;
}

bool MovieOrShow::operator<(const MovieOrShow &rhs) const {
    if (IMDbRating != rhs.IMDbRating) {
        return IMDbRating < rhs.IMDbRating;
    }
    return title < rhs.title;
}

MovieOrShow::Type MovieOrShow::getType() const {
    return type;
}

int MovieOrShow::getReleaseYear() const {
    return releaseYear;
}

bool MovieOrShow::mosComperator::operator()(MovieOrShow lhs, MovieOrShow rhs) const {
    return lhs < rhs;
}