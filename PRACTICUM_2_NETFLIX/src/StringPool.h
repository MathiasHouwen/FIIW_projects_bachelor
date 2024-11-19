// volledig gemaakt door ebbe
// doel: elementen met identieke string waarde een identieke pointer kunnen geven
//      is handig voor genres: meerdere movies hebben dezelde genre pointer
//      voordeel string comparison is niet nodig, pointers kunnen direct compared worden O(1)


#ifndef PRACTICUM_2_NETFLIX_STRINGPOOL_H
#define PRACTICUM_2_NETFLIX_STRINGPOOL_H

#include <string>
#include <unordered_map>

using namespace std;

class StringPool {
private:
    ///@brief struct om een reference count te associeren met een string pointer
    struct SharedString{
        ///@brief pointer naar de shared string op de heap
        string* strPointer;
        ///@brief counter om te weten op hoeveel deze string in gebruik is (zodat die verwijderd kan als count 0 is)
        int referenceCount;
    };
    ///@brief map om voor elke string waarde de struct met de gedeelde pointer te vinden
    unordered_map<string, SharedString> pool{};
public:
    /**
     * @brief registreert een string en geeft de string pointer van de heap terug.
     * @complexiteit O(1)
     * @details
     *  * als de string nog niet bestaat komt dit overeen met auto s = new string("test");\n
     *  * als een identieke string waarde al in gebruik is, krijg je de bestaande pointer. Zo krijgt iedereen met een identieke string waarde ook een identieke string pointer.\n
     * @param str: string waarde waarvoor je een pointer wil krijgen
     * @return pointer naar de gedeelde string op de heap
     * @author ebbe
     */
    string* use(const string& str);
    /**
     * @brief laat de pool weten dat je de string niet meer gebruikt
     * @complexiteit O(1)
     * @details
     *  * verwijdert de string enkel van de heap als helemaal niemand die string gebruikt
     * @param str: waarde van de string die je niet meer wil gebruiken
     * @author ebbe
     */
    void unuse(const string& str);
};

#endif //PRACTICUM_2_NETFLIX_STRINGPOOL_H
