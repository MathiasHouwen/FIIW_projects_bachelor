//
// Created by ebbew on 19-11-2024.
//

#ifndef PRACTICUM_2_NETFLIX_STRINGPOOL_H
#define PRACTICUM_2_NETFLIX_STRINGPOOL_H

#include <string>
#include <unordered_map>

using namespace std;

class StringPool {
private:
    struct SharedString{
        string* strPointer;
        int referenceCount;
    };
    unordered_map<string, SharedString> pool{};
public:
    string* use(const string& str);
    void unuse(const string& str);
};


#endif //PRACTICUM_2_NETFLIX_STRINGPOOL_H
