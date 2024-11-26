//
// Created by ebbew on 20-11-2024.
//

#include <sstream>
#include <utility>
#include "MovieOrShow.h"

string MovieOrShow::toString() {
    stringstream ss;
    ss << title << "[ genre: " << *genre << " IDMb: " << IMDbRating << " ]";
    return ss.str();
}

bool MovieOrShow::operator<(const MovieOrShow &rhs) const {
    if (IMDbRating != rhs.IMDbRating) {
        return IMDbRating < rhs.IMDbRating;
    }
    return title < rhs.title;
}

MovieOrShow::MovieOrShow(string title, string *genre, float imDbRating) : title(std::move(title)), genre(genre),
                                                                                       IMDbRating(imDbRating) {}

const string &MovieOrShow::getTitle() const {
    return title;
}

string *MovieOrShow::getGenre() const {
    return genre;
}

const float MovieOrShow::getImDbRating() const {
    return IMDbRating;
}

bool MovieOrShow::operator==(const MovieOrShow &rhs) const {
    return title == rhs.title &&
           genre == rhs.genre; // rating wordt niet vergeleken. Movie or show is enkel uniek per title en genre
}

bool MovieOrShow::operator!=(const MovieOrShow &rhs) const {
    return !(rhs == *this);
}

