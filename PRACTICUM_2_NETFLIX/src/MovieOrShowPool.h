// volledig gemaakt door ebbe
// doel: movies or shows poolen, waarbij het poolen van hun genre strings intern kan gebeuren.
//          deze class is dus een pool voor movie or show en een abstractie laag over de genres
// composition ipv inheritance omdat use/unuse/peek geen override kunnen hebben omdat ze niet virtual zijn

#ifndef PRACTICUM_2_NETFLIX_MOVIEORSHOWPOOL_H
#define PRACTICUM_2_NETFLIX_MOVIEORSHOWPOOL_H


#include "MovieOrShow.h"
#include "Pool.h"

using namespace std;

class MovieOrShowPool{

private:
    ///@brief pool voor de movies or shows
    Pool<MovieOrShow> pool;
    /// @brief pool voor de genre strings (meerdere movies sharen een genre. Vandaar ook pointer in de MovieOrShow class)
    Pool<string> genresPool;
public:
    /**
     * @brief idem aan Pool::use
     * @details verschil is dat deze ook de genres van het MovieOrShow managed via een aparte pool
     * @param mos: movie or show waarvoor je een pointer wil krijgen
     * @return: pointer naar de movie or show op de heap
     * @author ebbe
     */
    MovieOrShow* use(const MovieOrShow &mos);
    /**
     * @brief idem aan Pool::use
     * @details verschil is dat deze ook de genres van het MovieOrShow managed via een aparte pool
     * @param mos: movie or show dat je niet meer wil gebruiken
     * @author ebbe
     */
    void unuse(const MovieOrShow &mos);
    /**
     * @brief idem aan Pool::use
     * @details verschil is dat deze ook de genres van het MovieOrShow managed via een aparte pool
     * @param mos: movie or show waarvoor je een pointer wil krijgen (null als niet bestaat)
     * @return pointer naar het gedeelde object op de heap
     * @author ebbe
     */
    MovieOrShow* peek(const MovieOrShow &mos);
};


#endif //PRACTICUM_2_NETFLIX_MOVIEORSHOWPOOL_H
