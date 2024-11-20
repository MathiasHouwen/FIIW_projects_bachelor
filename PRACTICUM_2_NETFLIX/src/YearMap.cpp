//
// Created by houwe on 20/11/2024.
//

#include "YearMap.h"

void YearMap::insert(MovieOrShow mos) {
    if(mos.getType() == MovieOrShow::Type::movie){
        return insert(mos, movieHash);
    }
    return insert(mos, serieHash);
}

void YearMap::insert(MovieOrShow mos, unordered_map<int, mosSet *> hashMap) {
    mosSet *set = hashMap[mos.getReleaseYear()];
    set->insert(mos);
}

void YearMap::remove(MovieOrShow mos) {
    if(mos.getType() == MovieOrShow::Type::movie){
        return remove(mos, movieHash);
    }
    return remove(mos, serieHash);
}

void YearMap::remove(MovieOrShow mos, unordered_map<int, mosSet *> hashMap) {
    mosSet *set = hashMap[mos.getReleaseYear()];
    set->erase(mos);
}
