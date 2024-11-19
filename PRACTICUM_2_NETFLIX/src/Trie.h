//
// Created by robin on 19/11/2024.
//

#ifndef TRIESTRUCTURE_H
#define TRIESTRUCTURE_H
#include <string>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    unordered_map<char, Node*> children{};
    bool stop{false};
};

class Trie {
    public:
        Trie();
        ~Trie() = default;
        void insertString(string word);
        //bool search(string word);
        //bool startsWith(string prefix);
    private:
        Node* root;
        void insertLetter(int letterIndex, string word, Node *node);
        int tracker = 0;
};



#endif //TRIESTRUCTURE_H
