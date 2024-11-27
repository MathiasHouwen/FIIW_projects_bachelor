// door iedereen aan gewerkt
// doel: data van een movie of tv show

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOW_H

#include <string>
#include <unordered_set>

class MovieOrShow {
public:
    ///@brief set voor string pointers, gebruikt voor genres
    using StringSet = std::unordered_set<std::string *>;
    MovieOrShow(std::string title, StringSet genres, float imDbRating, std::string id);

    ///@brief maakt mooie string om te printen
    std::string toString();

    /// @brief relatie op basis van IMDb en title
    bool operator<(const MovieOrShow &rhs) const;
    ///@brief vergelijking op basis van ID
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

///@brief gebruikt voor sets/queus die MovieORShow objecten moeten sorteren
struct ComparableMovieOrShowPointer{
    MovieOrShow* mos;
    bool operator<(const ComparableMovieOrShowPointer &rhs) const;
    bool operator>(const ComparableMovieOrShowPointer &rhs) const;
};

#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOW_H
