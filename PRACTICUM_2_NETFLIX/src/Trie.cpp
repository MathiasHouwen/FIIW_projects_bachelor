//
// Created by robin on 19/11/2024.
//

#include "Trie.h"

#include <iostream>
#include <ostream>
#include <utility>

Trie::Trie() {
    root = new Node();
}

void Trie::insertString(string word) {
    insertLetter(0, std::move(word), root);
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

vector<string> Trie::search(string prefix) {
    vector<string> result;
    Node* currentNode = root;

    for (char letter : prefix) {
        if (!currentNode->children.contains(letter)) {
            return result;
        }
        currentNode = currentNode->children[letter];
    }

    collectWords(prefix, currentNode, result);
    return result;
}

void Trie::collectWords(string currentWord, Node* node, vector<string>& result) {
    if (node->stop) {
        result.push_back(currentWord);
    }

    for (auto& child : node->children) {
        char letter = child.first;
        Node* childNode = child.second;
        collectWords(currentWord + letter, childNode, result);
    }
}

string Trie::findWords(string temporaryWord, Node* node, string prefix) {
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