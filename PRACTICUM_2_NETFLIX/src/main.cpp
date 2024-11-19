//
// Created by robin on 18/11/2024.
//


#include <internal/csv_reader.hpp>

#include "Trie.h"

using namespace csv;
int main() {
    //CSVReader reader("../data/netflixdata.csv");
    auto trie = new Trie();
    trie->insertString("hello");
    trie->insertString("wereldjes");
    trie->insertString("hel");
    trie->insertString("helcat");
    return 0;
}
