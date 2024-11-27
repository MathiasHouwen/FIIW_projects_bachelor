// volledig gemaakt door ebbe
// doel: movies or shows poolen, waarbij het poolen van hun genre strings intern kan gebeuren.
//          deze class is dus een pool voor movie or show en een abstractie laag over de genres
// composition ipv inheritance omdat use/unuse/peek geen override kunnen hebben omdat ze niet virtual zijn

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOWPOOL_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOWPOOL_H


#include <vector>
#include "MovieOrShow.h"
#include "Pool.h"

class MovieOrShowPool{
private:
    ///@brief pool voor de movies or shows, string = ID
    Pool<std::string, MovieOrShow> pool;
    /// @brief pool voor de genre strings (meerdere movies sharen een genre. Vandaar ook pointer in de MovieOrShow class)
    Pool<std::string> genresPool;
public:
    using StringSet = std::unordered_set<std::string>;
    MovieOrShowPool();
    /**
     * @brief idem aan Pool::use
     * @details verschil is dat deze ook de genres van het MovieOrShow managed via een aparte pool\n
     * Construct ook de movie or show vanuit parameters
     * @param title: title van movie or show
     * @param genre: genre van movie or show
     * @param IMDbRating: rating van movie or show
     * @return: pointer naar de movie or show op de heap
     * @author ebbe
     */
    MovieOrShow* use(const std::string& title, const StringSet& genres, const float IMDbRating, const std::string& id);
    /**
     * @brief idem aan Pool::use
     * @details
     * verschil is dat deze ook de genres van het MovieOrShow managed via een aparte pool\n
     * gebruikt enkel de minimale parameters voor een unieke movie or show (dus geen IMDbRating)
     * @param title: movie or show waarvoor je een pointer wil krijgen (null als niet bestaat)
     * @param genre
     * @author ebbe
     */
    void unuse(const std::string& id);
    /**
     * @brief idem aan Pool::use
     * @details
     * verschil is dat deze ook de genres van het MovieOrShow managed via een aparte pool\n
     * ebruikt enkel de minimale parameters voor een unieke movie or show (dus geen IMDbRating)
     * @param title: movie or show waarvoor je een pointer wil krijgen (null als niet bestaat)
     * @param genre
     * @return pointer naar het gedeelde object op de heap
     * @author ebbe
     */
    MovieOrShow* peek(const std::string& id) const;
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOWPOOL_H
