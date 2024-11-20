//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOW_H

#include <string>

using namespace std;

class MovieOrShow {
public:
    MovieOrShow(string title, string *genre, float imDbRating);
    string toString();
    bool operator<(const MovieOrShow &rhs) const;

    const string &getTitle() const;
    string *getGenre() const;
    const float getImDbRating() const;
private:
    const string title;
    string* genre; // dit is een pointer omdat genres gedeeld worden (via string pool)
    const float IMDbRating;
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
