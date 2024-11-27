//
// Created by ebbew on 20-11-2024.
//

#include <sstream>
#include <utility>
#include "MovieOrShow.h"

using namespace std;

string MovieOrShow::toString() {
    stringstream ss;
    ss << title;
    for(int _ = 0; _ < 50 - title.size(); _++){
        ss << ".";
    }
    ss << "[" << id << "]";
    ss << "   IMDb: " << IMDbRating;
    return ss.str();
}

bool MovieOrShow::operator<(const MovieOrShow &rhs) const {
    if (IMDbRating != rhs.IMDbRating) {
        return IMDbRating > rhs.IMDbRating;
    }
    return title < rhs.title;
}

MovieOrShow::MovieOrShow(string title, StringSet genres, float imDbRating, string id) : title(std::move(title)), genres(genres),
                                                                                       IMDbRating(imDbRating), id(id) {}

const string &MovieOrShow::getTitle() const {
    return title;
}

const float MovieOrShow::getImDbRating() const {
    return IMDbRating;
}

bool MovieOrShow::operator==(const MovieOrShow &rhs) const {
    return IMDbRating == rhs.IMDbRating;
}

bool MovieOrShow::operator!=(const MovieOrShow &rhs) const {
    return !(rhs == *this);
}

const unordered_set<std::string *> &MovieOrShow::getGenres() const {
    return genres;
}

const string &MovieOrShow::getId() const {
    return id;
}

