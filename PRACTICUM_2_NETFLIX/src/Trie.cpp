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
        if (!currentNode->children.contains(letter)) {
            if(result.empty()) {
                cout << "No Titles found" << endl;
            }
            return result;
        }
        currentNode = currentNode->children[letter];
    }

    // bouw alle woorden vanaf de prefix
    collectWords(prefix, currentNode, result);
    return result;
}

void Trie::deleteString(const string& word) {
    if (deleteHelper(root, word, 0)) {
        cout << "Removed: " << word << endl;
    } else {
        cout << "Failed to remove: " << word << endl;
    }
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

bool Trie::deleteHelper(Node* node, const string& word, int depth) {
    if (depth == word.length()) {
        if (!node->stop) return false; // Word not found
        return true;
    }

    char letter = word[depth];
    if (!node->children.contains(letter)) return false;

    Node* child = node->children[letter];
    bool shouldDeleteChild = deleteHelper(child, word, depth + 1);

    if (shouldDeleteChild) {
        delete child;
        node->children.erase(letter);
        return node->children.empty() && !node->stop;
    }
    return false;
}