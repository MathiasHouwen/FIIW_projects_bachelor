// taakverdeling + functies documentatie: zie h-file

#include "Pool.h"

template<typename Key, typename Value>
Value *Pool<Key, Value>::use(const Value &object, const Key& separateKey) {
    // als object nog nooit eerder gebruikt was:
    // - maak object op heap
    // - insert in pool, met ref count 1
    if(!pool.contains(separateKey)){
        auto objPointer = new Value(object);
        pool[separateKey] = SharedObject{objPointer, 1};
        return objPointer;
    }
    // als string al bestaat:
    // increase ref count en return de bestaande heap pointer
    SharedObject& sharedString = pool[separateKey];
    sharedString.referenceCount++;
    return sharedString.strPointer;
}

template<typename Key, typename Value>
Value *Pool<Key, Value>::use(const Value &object) {
    use(object, object);
}

template<typename Key, typename Value>
Value *Pool<Key, Value>::peek(const Key &object) const {
    if(pool.contains(object))
        return pool[object];
    else
        return nullptr;
}

template<typename Key, typename Value>
void Pool<Key, Value>::unuse(const Key &object) {
    // als object niet bestaat is die al unused (edge case, zou eig nooit hoeven gebeuren)
    if(!pool.contains(object)) return;

    // een unuse verminderd de ref count
    SharedObject& sharedString = pool[object];
    sharedString.referenceCount--;
    // als de object helemaal niet meer gebruikt wordt, delete van heap en uit de pool
    if(sharedString.referenceCount == 0){
        delete sharedString.strPointer;
        pool.erase(object);
    }
}

template<typename Key, typename Value>
Pool<Key, Value>::Pool() {
    pool = unordered_map<Key, SharedObject>{};
}