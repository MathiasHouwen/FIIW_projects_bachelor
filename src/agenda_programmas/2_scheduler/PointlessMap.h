//
// Created by ebbew on 21-10-2024.
//

#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_POINTLESSMAP_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_POINTLESSMAP_H

#include <vector>

template <typename T>
class PointlessMap {
private:
    const static short end = 15; // bespaard size-1 berekeningen
    struct Cell{
        bool occupied:1{false};
        bool pointsToNext:1{true}; // next of prev
        short index{-1};
        Cell(bool occupied, short index);
        Cell()= default;
    };
    Cell indexer[end+1]{};
    std::vector<T> storage{};
public:
    void insert(short index, T item);
    T get(short index);
    short getNext(short index);
    short getFirstIndex();
    short getLastIndex();
};




#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_POINTLESSMAP_H
