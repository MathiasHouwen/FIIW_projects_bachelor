// taakverdeling + functies documentatie: zie h-file

#include "Trie.h"

#include <iostream>
#include <ostream>
#include <utility>

// ======================================
// Public:
// ======================================

Trie::Trie() {
    root = new Node();
}

void Trie::insertString(const string& word) {
    insertLetter(0, word, root);
}

vector<string> Trie::search(const string& prefix) {
    vector<string> result;
    Node* currentNode = root;

    // check of prefix volledig bestaat vanaf de root node
    for (char letter : prefix) {
        if (!currentNode->children.contains(letter))
            return result;
        currentNode = currentNode->children[letter];
    }

    // bouw alle woorden vanaf de prefix
    collectWords(prefix, currentNode, result);
    return result;
}

// ======================================
// Private:
// ======================================

void Trie::insertLetter(int letterIndex, const string& word, Node *node) {
    // als je de laatste letter van het woord bereikt, word de node als end-of-word gemarkeerd door stop=true
    if (letterIndex == word.length()) {
        node->stop = true;
        return;
    }
    // bepaal de child node voor de huidige letter
    // als die bestaat, pak die, anders maak nieuwe
    char letter = word[letterIndex];
    Node* childNode;
    if (node->children.contains(letter))
        childNode = node->children[letter];
    else{
        childNode = new Node();
        node->children[letter] = childNode;
    }
    // insert verder met de volgende letter, vanaf de child node
    insertLetter(letterIndex+1, word, childNode);
}



// result is een out-parameter -> geen gedoe met return vectors mergen, elegantere code
void Trie::collectWords(const string& currentWord, Node *node, vector<string> &result) {
    // stop = true markeert het einde van een woord (maar niet perse het einde van de branch)
    if (node->stop) {
        result.push_back(currentWord);
    }

    // visit alle children om uit alle verdere branches woorden te vinden
    for (auto& child : node->children) {
        char letter = child.first;
        Node* childNode = child.second;
        collectWords(currentWord + letter, childNode, result);
    }
}

string Trie::findWords(string& temporaryWord, Node* node, const string& prefix) {
    Node* currentNode = node;
    for (size_t i = temporaryWord.length(); i < prefix.length(); ++i) {
        char letter = prefix[i];
        if (!currentNode->children.contains(letter)) {
            cout << "No such Title" << endl;
            return "";
        }
        currentNode = currentNode->children[letter];
        temporaryWord += letter;
    }
    return temporaryWord;
}