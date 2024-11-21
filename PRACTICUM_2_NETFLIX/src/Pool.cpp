// taakverdeling + functies documentatie: zie h-file

#include "Pool.h"

template<typename T>
T *Pool<T>::use(const T& object) {
    // als string nog nooit eerder gebruikt was:
    // - maak string op heap
    // - insert in pool, met ref count 1
    if(!pool.contains(object)){
        auto strPointer = new T(object);
        pool[object] = SharedObject{strPointer, 1};
        return strPointer;
    }
    // als string al bestaat:
    // increase ref count en return de bestaande heap pointer
    SharedObject& sharedString = pool[object];
    sharedString.referenceCount++;
    return sharedString.strPointer;
}

template<typename T>
void Pool<T>::unuse(const T& object) {
    // als string niet bestaat is die al unused (edge case, zou eig nooit hoeven gebeuren)
    if(!pool.contains(object)) return;

    // een unuse verminderd de ref count
    SharedObject& sharedString = pool[object];
    sharedString.referenceCount--;
    // als de string helemaal niet meer gebruikt wordt, delete van heap en uit de pool
    if(sharedString.referenceCount == 0){
        delete sharedString.strPointer;
        pool.erase(object);
    }
}

template<typename T>
T* Pool<T>::peek(const T &object) {
    if(pool.contains(object))
        return pool[object];
    else
        return nullptr;
}