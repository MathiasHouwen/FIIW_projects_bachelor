// volledig gemaakt door ebbe
// doel: elementen met identieke string waarde een identieke pointer kunnen geven
//      is handig voor genres: meerdere movies hebben dezelde genre pointer
//      voordeel string comparison is niet nodig, pointers kunnen direct compared worden O(1)
// aanpassing:
//      is later generic gemaakt (niet meer string specifiek) met templat
//      -> kan dan ook gebruikt worden om MoveOrShow objects te delen tussen de Trie en YearMap


#ifndef PRACTICUM_2_NETFLIX_POOL_H
#define PRACTICUM_2_NETFLIX_POOL_H

#include <unordered_map>
#include <string>
#include "MovieOrShow.h"


template<typename K, typename V=K>
class Pool {
private:
    ///@brief struct om een reference count te associeren met een pointer
    struct SharedObject{
        ///@brief pointer naar het shared object op de heap
        V* strPointer;
        ///@brief counter om te weten op hoeveel dit object in gebruik is (zodat die verwijderd kan als count 0 is)
        int referenceCount;
    };
    ///@brief map om voor elke object waarde de struct met de gedeelde pointer te vinden
    std::unordered_map<K, SharedObject> objectPool;
public:
    Pool();
    /**
     * @brief registreert een object en geeft de object pointer van de heap allocatie terug.
     * @complexiteit O(1)
     * @details
     *  * als object nog niet bestaat komt dit overeen met auto t = new T(...);\n
     *  * als een identiek object al in gebruik is, krijg je de bestaande pointer. Zo krijgt iedereen met een identieke waarde ook een identieke pointer.\n
     * @param object: waarde waarvoor je een pointer wil krijgen
     * @return pointer naar de gedeelde object op de heap
     * @author ebbe
     */
    V* use(const V& object, const K& separateKey);

    /**
     * @brief laat de pool weten dat je het object niet meer gebruikt
     * @complexiteit O(1)
     * @details
     *  * verwijdert het object enkel van de heap als helemaal niemand dat object gebruikt
     * @param str: waarde van het object die je niet meer wil gebruiken
     * @author ebbe
     */
    void unuse(const K& object);

    /**
     * @brief returnt de pointer van een bestaand object. Dit is voor als je kort de pointer waarde wil "bekijken" zonder de pool state aan te passen.
     * @param object: waarde waarvoor je een pointer wil krijgen (null als niet bestaat)
     * @return pointer naar de gedeelde object op de heap
     * @author ebbe
     */
    V* peek(const K& object) const;
};


#endif //PRACTICUM_2_NETFLIX_POOL_H
