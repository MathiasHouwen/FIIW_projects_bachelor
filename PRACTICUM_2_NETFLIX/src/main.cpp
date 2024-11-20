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
    MovieOrShow movie1 = {MovieOrShow::Type::movie,2000,"Armageddon", action, 5.5};
    MovieOrShow movie2 = {MovieOrShow::Type::movie, 2010,"Cars", romance, 9.5};
    MovieOrShow movie3 = {MovieOrShow::Type::serie,1998,"Arme man", romance, 5.5};
    Trie *trie = new Trie();
    trie->insertMOS(&movie1);
    trie->insertMOS(&movie2);
    trie->insertMOS(&movie3);
    for(string s:trie->search("Arm", romance)) {
        cout << s << endl;
    }
    return 0;
}
