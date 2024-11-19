// taakverdeling + functies documentatie: zie h-file

#include "StringPool.h"

string *StringPool::use(const string& str) {
    // als string nog nooit eerder gebruikt was:
    // - maak string op heap
    // - insert in pool, met ref count 1
    if(!pool.contains(str)){
        auto strPointer = new string(str);
        pool[str] = SharedString{strPointer, 1};
        return strPointer;
    }
    // als string al bestaat:
    // increase ref count en return de bestaande heap pointer
    SharedString& sharedString = pool[str];
    sharedString.referenceCount++;
    return sharedString.strPointer;
}

void StringPool::unuse(const string& str) {
    // als string niet bestaat is die al unused (edge case, zou eig nooit hoeven gebeuren)
    if(!pool.contains(str)) return;

    // een unuse verminderd de ref count
    SharedString& sharedString = pool[str];
    sharedString.referenceCount--;
    // als de string helemaal niet meer gebruikt wordt, delete van heap en uit de pool
    if(sharedString.referenceCount == 0){
        delete sharedString.strPointer;
        pool.erase(str);
    }
}
