//
// Created by ebbew on 19-11-2024.
//

#include "StringPool.h"

string *StringPool::use(const string& str) {
    if(!pool.contains(str)){
        auto strPointer = new string(str);
        pool[str] = SharedString{strPointer, 1};
        return strPointer;
    }
    SharedString& sharedString = pool[str];
    sharedString.referenceCount++;
    return sharedString.strPointer;
}

void StringPool::unuse(const string& str) {
    if(!pool.contains(str)) return;

    SharedString& sharedString = pool[str];
    sharedString.referenceCount--;
    if(sharedString.referenceCount == 0){
        delete sharedString.strPointer;
        pool.erase(str);
    }
}
