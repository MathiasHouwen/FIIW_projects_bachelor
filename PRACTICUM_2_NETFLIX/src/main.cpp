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

    auto trie = new Trie();
    trie->insertString("hello");
    trie->insertString("wereldjes");
    trie->insertString("hel");
    trie->insertString("helcat");
    trie->deleteString("hel");

    vector<string> found = trie->search("hel");
    for (int i = 0; i < found.size(); i++) {
        cout << found[i] << endl;
    }

    return 0;
}
