//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOW_H

#include <string>

using namespace std;

class MovieOrShow {
public:
    enum class Type{movie, serie};

    MovieOrShow(Type type, int releaseYear, const string &title, string *genre, float imDbRating);

    const string &getTitle() const;
    string *getGenre() const;
    float getImDbRating() const;
    string toString();

    struct mosComperator{
        bool operator()(MovieOrShow lhs, MovieOrShow rhs) const;
    };
    bool operator<(const MovieOrShow &rhs) const;

    Type getType() const;
    int getReleaseYear() const;

private:
    Type type;
    int releaseYear;
    string title;
    string* genre;
    float IMDbRating;
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
