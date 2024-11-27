// gemaakt door robin
// doel: datastructuur om snel te zoeken op basis van prefix

#ifndef TRIESTRUCTURE_H
#define TRIESTRUCTURE_H
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "MovieOrShow.h"

#define maxSize 10

using mosque = std::priority_queue<ComparableMovieOrShowPointer, std::vector<ComparableMovieOrShowPointer>, std::greater<ComparableMovieOrShowPointer>>;

/**
 * @brief node in de trie boom\n\n
 * @details
 * De enige flag is stop:\n
 *  * stop = true -> node = laaste letter van een woord\n\n
 * Al de rest wordt via de size van de map bepaald:\n
 *  * size == 1 -> midden in een suffix\n
 *  * size == 0 -> leaf node\n
 *  * size > 1 -> meerdere branches\n
 */
struct NodeValue{
    using GenreToMOSMap = std::unordered_map<std::string*, MovieOrShow*>;
    GenreToMOSMap genreToMOSMap{};
};
struct Node {
    ///@brief alle child nodes, gemapt op hun letter. Letter is niet opgeslagen in de node zelf.
    std::unordered_map<char, Node*> children{};
    ///@brief flag die markeerd of deze node de eindletter van een woord is.
    bool stop{false};
    NodeValue value;
};

class Trie {
public:
    Trie();
    ~Trie() = default;
    /**
    * @brief een woord/string toe aan de trie.
    * @complexiteit O(???)
    * @details Gebruikt recursief de insertLetter functie.
    * @param word: Woord om toe te voegen.
     * @author robin
    */
    void insertMOS(MovieOrShow* mos);
    /**
     * @brief alle strings in de trie die beginnen met de prefix
     * @complexiteit O(???)
     * @param prefix: prefix waarmee je wil zoeken
     * @return vector van alle matches
     * @author robin
     */
    std::vector<MovieOrShow*> search(const std::string& prefix, std::string* genre);
    void deleteMOS(MovieOrShow* mos);

private:
    /// @brief root node van de tree
    Node* root;
    /**
     * @brief help functie om woord letter per letter (= node per node) toe te vogen
     * @complexiteit O(???)
     * @param letterIndex: index van de huidig toe te voegen letter van het woord
     * @param word: volledige toe te voegen woord
     * @param node: huidige node, waarvan de huidige letter een child node is/wordt
     * @author robin
     */
    void insertLetter(int letterIndex, MovieOrShow* mos, Node *node);

    /**
     * @brief helper functie. Verzamelt alle matchende woorden vanaf de prefix.
     * @complexiteit O(???)
     * @param currentWord: prefix + visited letters
     * @param node: huidige node
     * @param result: out-parameter waar gevonden volledige woorden in worden gegooid
     * @author robin
     */
    void collectWords(const std::string &currentWord, Node *node, mosque &result, std::string* genre);
    bool deleteHelper(Node *node, MovieOrShow* mos, int depth);
};



#endif //TRIESTRUCTURE_H
