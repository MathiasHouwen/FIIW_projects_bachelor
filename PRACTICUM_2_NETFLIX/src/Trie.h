// gemaakt door robin
// doel: datastructuur om snel te zoeken op basis van prefix

#ifndef TRIESTRUCTURE_H
#define TRIESTRUCTURE_H
#include <string>
#include <unordered_map>
#include <vector>

#include "MovieOrShow.h"
using namespace std;

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
struct Node {
    ///@brief alle child nodes, gemapt op hun letter. Letter is niet opgeslagen in de node zelf.
    unordered_map<char, Node*> children{};
    ///@brief flag die markeerd of deze node de eindletter van een woord is.
    bool stop{false};
    MovieOrShow* movieOrShow{nullptr};
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
    vector<string> search(const string& prefix);
    void deleteString(const string& word);

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
    void collectWords(const string& currentWord, Node *node, vector<string> &result);
    bool deleteHelper(Node *node, const string &word, int depth);
};



#endif //TRIESTRUCTURE_H
