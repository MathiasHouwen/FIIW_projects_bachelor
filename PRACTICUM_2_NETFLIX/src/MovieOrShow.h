//
// Created by ebbew on 20-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOW_H

#include <string>
#include <unordered_set>

class MovieOrShow {
public:
    using StringSet = std::unordered_set<std::string *>;
    MovieOrShow(std::string title, StringSet genres, float imDbRating, std::string id);

    std::string toString();

    bool operator<(const MovieOrShow &rhs) const;
    bool operator==(const MovieOrShow &rhs) const;
    bool operator!=(const MovieOrShow &rhs) const;


    const std::string &getId() const;
    const std::string &getTitle() const;
    const float getImDbRating() const;
    const StringSet &getGenres() const;

private:
    const std::string title;
    const std::string id;
    StringSet genres; // dit is een pointer omdat genres gedeeld worden (via string pool)
    const float IMDbRating;
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
