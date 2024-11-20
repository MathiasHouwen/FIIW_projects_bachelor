//
// Created by ebbew on 20-11-2024.
//

#include <sstream>
#include "MovieOrShow.h"

MovieOrShow::MovieOrShow(const string &title, string *genre, float imDbRating) : title(title), genre(genre),
                                                                                 IMDbRating(imDbRating) {}

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
