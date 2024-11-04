//
// Volledig gemaakt door Ebbe
//


#ifndef ALDA_TEAM3_EBBE_ROBIN_MATHIAS_POINTLESSMAP_H
#define ALDA_TEAM3_EBBE_ROBIN_MATHIAS_POINTLESSMAP_H

#include <vector>

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // FOR FULL DISCUSSION OF ALGORITHMS AND DATASTRUCTURES -> CHECK docs -> Discussion.md
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

template <typename T>
class PointlessMap {
private:
    const static short end = 364; // end ipv size bespaard size-1 berekeningen
    struct Cell{
        bool occupied:1{false};
        bool pointsToNext:1{true}; // next of prev
        short index{-1};
        Cell()= default;
    };
    Cell indexer[end+1]{};
    std::vector<T> storage{};
public:
    void insert(short index, const T& item); // TODO O(?)
    T& get(short index); // O(1)
    short getNext(short index); // O(1)
    short getFirstIndex(); // O(1)
    short getLastIndex(); // O(1)
    bool contains(short index); // O(1)
    bool isEmpty();
};



#endif //ALDA_TEAM3_EBBE_ROBIN_MATHIAS_POINTLESSMAP_H
