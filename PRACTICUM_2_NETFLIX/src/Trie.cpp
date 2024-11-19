//
// Created by robin on 19/11/2024.
//

#include "Trie.h"

Trie::Trie() {
    root = new Node();
}

void Trie::insertString(string word) {
    insertLetter(0, word, root);
}

void Trie::insertLetter(int letterIndex, string word, Node* node) {
    if (letterIndex == word.length()) {
        node->stop = true;
        return;
    }
    char letter = word[letterIndex];
    if (!node->children.contains(letter)) {
        node->children[letter] = new Node();
    }
    insertLetter(letterIndex+1, word, node->children[letter]);
}