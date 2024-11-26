//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOW_H

#include <string>

class MovieOrShow {
public:
    MovieOrShow(std::string title, std::string *genre, float imDbRating);
    std::string toString();
    bool operator<(const MovieOrShow &rhs) const;
    bool operator==(const MovieOrShow &rhs) const;
    bool operator!=(const MovieOrShow &rhs) const;

    const std::string &getTitle() const;
    std::string *getGenre() const;
    const float getImDbRating() const;
private:
    const std::string title;
    std::string* genre; // dit is een pointer omdat genres gedeeld worden (via string pool)
    const float IMDbRating;
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
