//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOW_H

#include <string>

using namespace std;

class MovieOrShow {
private:
    string title;
    string* genre;
    float IMDbRating;
public:
    MovieOrShow(const string &title, string *genre, float imDbRating);
    const string &getTitle() const;
    string *getGenre() const;
    float getImDbRating() const;
    string toString();
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
