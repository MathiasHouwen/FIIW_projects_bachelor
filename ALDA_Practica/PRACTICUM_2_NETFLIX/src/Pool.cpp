// taakverdeling + functies documentatie: zie h-file

#include "Pool.h"

template<typename K, typename V>
V *Pool<K, V>::use(const V &object, const K& separateKey) {
    // als object nog nooit eerder gebruikt was:
    // - maak object op heap
    // - insert in pool, met ref count 1
    if(!objectPool.contains(separateKey)){
        auto objPointer = new V(object);
        objectPool[separateKey] = SharedObject{objPointer, 1};
        return objPointer;
    }
    // als string al bestaat:
    // increase ref count en return de bestaande heap pointer
    SharedObject& sharedString = objectPool[separateKey];
    sharedString.referenceCount++;
    return sharedString.strPointer;
}

template<typename K, typename V>
V *Pool<K, V>::peek(const K &object) const {
    if(objectPool.contains(object)){
        return objectPool.at(object).strPointer;
    }
    else
        return nullptr;
}

template<typename K, typename V>
void Pool<K, V>::unuse(const K &object) {
    // als object niet bestaat is die al unused (edge case, zou eig nooit hoeven gebeuren)
    if(!objectPool.contains(object)) return;

    // een unuse verminderd de ref count
    SharedObject& sharedString = objectPool[object];
    sharedString.referenceCount--;
    // als de object helemaal niet meer gebruikt wordt, delete van heap en uit de pool
    if(sharedString.referenceCount == 0){
        delete sharedString.strPointer;
        objectPool.erase(object);
    }
}

template<typename K, typename V>
Pool<K, V>::Pool() : objectPool(){
}

template class Pool<std::string, std::string>;
template class Pool<std::string, MovieOrShow>;