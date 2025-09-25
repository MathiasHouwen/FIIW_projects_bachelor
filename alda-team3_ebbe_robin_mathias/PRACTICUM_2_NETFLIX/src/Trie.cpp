// taakverdeling + functies documentatie: zie h-file

#include "Trie.h"

#include <algorithm>
#include <iostream>
#include <ostream>

using namespace std;

// ======================================
// Public:
// ======================================

Trie::Trie() {
    root = new Node();
}

void Trie::insertMOS(MovieOrShow* mos) {
    insertLetter(0, mos, root);
}

vector<MovieOrShow*> Trie::search(const string& prefix, string* genre) {
    vector<MovieOrShow*> sortedResult;
    mosque result;
    Node* currentNode = root;

    // check of prefix volledig bestaat vanaf de root node
    for (char letter : prefix) {
        if (!currentNode->children.contains(letter)) {
            if(result.empty()) {
                cout << "No Titles found" << endl;
            }
            return sortedResult;
        }
        currentNode = currentNode->children[letter];
    }

    // bouw alle woorden vanaf de prefix
    unordered_set<string> chache;
    collectWords(prefix, currentNode, result, genre, chache);

    for(int i = 0; i < maxSize; i++) {
        if (result.empty()){break;}
        sortedResult.push_back(result.top().mos);
        result.pop();
    }
    return sortedResult;
}

void Trie::deleteMOS(MovieOrShow* mos) {
    deleteHelper(root, mos, 0);
    cout << "Removed: " << mos->getTitle() << endl;
}


// ======================================
// Private:
// ======================================

void Trie::insertLetter(int letterIndex, MovieOrShow* mos, Node *node) {
    string title = mos->getTitle();
    // als je de laatste letter van het woord bereikt, word de node als end-of-word gemarkeerd door stop=true
    if (letterIndex == title.length()) {
        node->stop = true;
        for(auto genre : mos->getGenres()){
            node->value.genreToMOSMap[genre] = mos;
        }
        return;
    }
    // bepaal de child node voor de huidige letter
    // als die bestaat, pak die, anders maak nieuwe
    char letter = title[letterIndex];
    Node* childNode;
    if (node->children.contains(letter))
        childNode = node->children[letter];
    else{
        childNode = new Node();
        node->children[letter] = childNode;
    }
    // insert verder met de volgende letter, vanaf de child node
    insertLetter(letterIndex+1, mos, childNode);
}



// result is een out-parameter -> geen gedoe met return vectors mergen, elegantere code
void Trie::collectWords(const string& currentWord, Node *node, mosque &result, string* genre, std::unordered_set<std::string>& resultTitlesChache) {
    // stop = true markeert het einde van een woord (maar niet perse het einde van de branch)
    if (node->stop) {

        if(!genre){
            for(auto mosEntry : node->value.genreToMOSMap){
                if(!resultTitlesChache.contains(mosEntry.second->getTitle()))
                    result.push(static_cast<priority_queue<ComparableMovieOrShowPointer>::value_type>(mosEntry.second));
                resultTitlesChache.insert(mosEntry.second->getTitle());
            }
        } else if(node->value.genreToMOSMap.contains(genre)){
            result.push(static_cast<priority_queue<ComparableMovieOrShowPointer>::value_type>(node->value.genreToMOSMap[genre]));
        }
    }

    // visit alle children om uit alle verdere branches woorden te vinden
    for (auto& child : node->children) {
        char letter = child.first;
        Node* childNode = child.second;
        collectWords(currentWord + letter, childNode, result, genre, resultTitlesChache);
    }
}

bool Trie::deleteHelper(Node* node, MovieOrShow* mos, int depth) {
    const string& word = mos->getTitle();
    if (depth == word.length()) {
        if (!node->stop) return false;
        node->stop = false;
        for(auto genre : mos->getGenres()){
            node->value.genreToMOSMap.erase(genre);
        }
        return node->children.empty();
    }

    char letter = word[depth];
    if (!node->children.contains(letter)) return false;

    Node* child = node->children[letter];
    bool shouldDeleteChild = deleteHelper(child, mos, depth + 1);

    if (shouldDeleteChild) {
        delete child;
        node->children.erase(letter);
        return node->children.empty() && !node->stop;
    }
    return false;
}