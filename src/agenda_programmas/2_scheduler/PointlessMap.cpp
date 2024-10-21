//
// Created by ebbew on 21-10-2024.
//

#include <stdexcept>
#include "PointlessMap.h"



template<typename T>
void PointlessMap<T>::insert(short index, T item) {
    if (index < 0 || index > end) throw std::runtime_error("Index out of range");

    Cell& cell = indexer[index];

    // edge case: cell heeft al een waarde:
    if (cell.occupied) {
        storage[cell.index] = item;
        return;
    }

    // get eerste en laaste cell indices
    Cell& cell0 = indexer[0];
    Cell& cellEnd = indexer[end];
    short firstIndex = cell0.occupied ? 0 : cell0.index;
    short lastIndex = cellEnd.occupied ? end : cellEnd.index;

    // edge case: volledig leeg:
    if(firstIndex == -1){
        cell0.index = index; // cell wordt first cell (als cell zelf 0 of end is wordt hieronder overgeschreven)
        cellEnd.index = index; // cell wordt last cell
        // insert
        cell.index = storage.size();
        cell.occupied = true;
        storage.push_back(item);
        return;
    }

    // edge cases: cell is nieuwe first of last:
    bool edgeCase = false;
    if(firstIndex - index > 1) { // edge case: index is nieuwe first of lijst is leeg
        Cell& prevPointer = indexer[firstIndex-1]; // prev van oude first wijst naar index
        prevPointer.pointsToNext = false;
        prevPointer.index = index;
        Cell& nextPointer = indexer[index+1]; // next van index wijst naar oude first
        nextPointer.pointsToNext = true;
        nextPointer.index = index;
        cell0.index = index; // cell wordt first
        edgeCase = true;
    } else if (index - lastIndex > 1){ // edge case: index is nieuwe last
        Cell& nextPointer = indexer[lastIndex+1]; // next van oude last wijst naar index
        nextPointer.pointsToNext = true;
        nextPointer.index = index;
        Cell& prevPointer = indexer[index-1]; // prev van index wijst naar oude last
        prevPointer.pointsToNext = false;
        prevPointer.index = index;
        cellEnd.index = index; // cell wordt first
        edgeCase = true;
    }
    if(edgeCase){
        // insert
        cell.index = storage.size();
        cell.occupied = true;
        storage.push_back(item);
        return;
    }

    // avarage case: cell zit tussen 2 neighbours
    short nextIndex;
    for(int i=index; i>=0; i--){ // zoek vorige next pointer
        Cell cellI = indexer[i];
        if(cellI.pointsToNext)
            nextIndex = indexer[cellI.index];
    }
    Cell& before = indexer[index-1]; // wordt nextpointer naar next
    Cell& after = indexer[index+1]; // wordt prevpointer naar prev
    Cell& nextBefore = indexer[nextIndex-1]; // wordt prevpointer naar index
    short prevIndex = nextBefore.pointsToNext ? index-2 : indexer[nextBefore.index];
    Cell& prevAfter = indexer[prevIndex+1]; // wordt nextpointer naar index
    // flags voor index
    if(!before.occupied){
        before.index = nextBefore.index;
        if(&before != &prevAfter){
            prevAfter.index = index;
        }
    }
    // flags na index
    if(!after.occupied){
        after.index = prevAfter.index;
        if(&after != &nextBefore){
            nextBefore.index = index;
        }
    }
}

template<typename T>
PointlessMap<T>::PointlessMap() {

}

template<typename T>
PointlessMap<T>::Cell::Cell(bool occupied, short index):occupied(occupied), index(index) {}
