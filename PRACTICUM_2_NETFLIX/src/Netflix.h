// gemaakt door iedereen
// doel: de main interface

#ifndef PRACTICUM_2_NETFLIX_NETFLIX_H
#define PRACTICUM_2_NETFLIX_NETFLIX_H


#include "Trie.h"
#include "YearMap.h"
#include "MovieOrShowPool.h"

enum class Type{MOVIE, SHOW};

class Netflix {
private:
    Trie moviesTrie{};
    Trie showsTrie{};

    YearMap moviesYearMap{};
    YearMap showsYearMap{};

    MovieOrShowPool movieOrShowPool;
public:
    using StringSet = std::unordered_set<std::string>;

    /**
     * @brief insert een nieuwe movie of show
     * @param type: movie of show
     * @param title: title
     * @param genres: set van genres
     * @param IMDbRating: IMDb
     * @param releaseYear: releaseYear
     * @param id: IMDbId
     */
    void insert(Type type, std::string title, StringSet genres, float IMDbRating, int releaseYear, std::string id);
    /**
     * @brief removed een movie of show, via minimale key: enkel ID
     * @param type: movie of show
     * @param id: IMDbId
     */
    void remove(Type type, std::string id);

    /**
     * Zoekt top 10 movie of shows op basis van partialTitle (en genre)
     * @param type: movie of show
     * @param partialTitle: partiele partialTitle string
     * @param genre: genre
     * @return: vector van top 10 (of minder) results
     */
    std::vector<MovieOrShow*> searchByTitle(Type type, const std::string& partialTitle, const std::string& genre = "");
    /**
     * Zoekt top 10 movie of shows op basis van release year
     * @param type: movie of show
     * @param releaseYear: releaseYear
     * @return: vector van top 10 (of minder) results
     */
    std::vector<MovieOrShow*> searchByReleaseYear(Type type, int releaseYear);

    Netflix() = default;
};


#endif //PRACTICUM_2_NETFLIX_NETFLIX_H
