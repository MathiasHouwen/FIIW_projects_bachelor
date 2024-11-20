//
// Created by robin on 18/11/2024.
//


#include <iostream>
#include <internal/csv_reader.hpp>
#include <iostream>

#include "Trie.h"
#include "StringPool.h"

using namespace csv;
using namespace std;

int main() {
    //CSVReader reader("../data/netflixdata.csv");
    auto* action = new string("action");
    auto* romance = new string("romance");
    MovieOrShow movie1 = {"Armageddon", action, 5.5};
    MovieOrShow movie2 = {"Cars", romance, 9.5};
    Trie *trie = new Trie();
    trie->insertMOS(&movie1);
    trie->insertMOS(&movie2);
    return 0;
}
