//
// Volledig gemaakt door Ebbe
//

#include <stdexcept>
#include "PointlessMap.h"
#include "SchedulerStructs.h"



template<typename T>
void PointlessMap<T>::insert(short index, const T& item) {
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
    if(index < firstIndex) { // edge case: index is nieuwe first of lijst is leeg
        Cell& prevPointer = indexer[firstIndex-1]; // prev van oude first wijst naar index
        prevPointer.pointsToNext = false;
        prevPointer.index = index;
        Cell& nextPointer = indexer[index+1]; // next van index wijst naar oude first
        if(!nextPointer.occupied){
            nextPointer.pointsToNext = true;
            nextPointer.index = firstIndex;
        }
        cell0.index = index; // cell wordt first
        edgeCase = true;
    } else if (index > lastIndex){ // edge case: index is nieuwe last
        Cell& prevPointer = indexer[index-1]; // prev van index wijst naar oude last
        if(!prevPointer.occupied){
            prevPointer.pointsToNext = false;
            prevPointer.index = lastIndex;
        }
        Cell& nextPointer = indexer[lastIndex+1]; // next van oude last wijst naar index
        nextPointer.pointsToNext = true;
        nextPointer.index = index;
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
        Cell& cellI = indexer[i];
        if(cellI.index != -1 && cellI.pointsToNext){
            nextIndex = cellI.index;
            break;
        }
    }
    Cell& before = indexer[index-1]; // wordt nextpointer naar next
    Cell& after = indexer[index+1]; // wordt prevpointer naar prev
    Cell& nextBefore = indexer[nextIndex-1]; // wordt prevpointer naar index
    short prevIndex = nextBefore.pointsToNext ? index-1 : nextBefore.index;
    Cell& prevAfter = indexer[prevIndex+1]; // wordt nextpointer naar index
    Cell oldPrevAfter = prevAfter;
    // flags voor index
    if(!before.occupied){
        before.index = nextBefore.index;
        prevAfter.index = index;
    }
    // flags na index
    if(!after.occupied){
        nextBefore.index = index;
        after.index = oldPrevAfter.index;
    }
    //insert
    cell.index = storage.size();
    cell.occupied = true;
    storage.push_back(item);
}

template<typename T>
short PointlessMap<T>::getNext(short index) {
    Cell& after = indexer[index+1];
    return after.occupied ? index+1 : after.index;
}

template<typename T>
T& PointlessMap<T>::get(short index) {
    return storage[indexer[index].index];
}

template<typename T>
short PointlessMap<T>::getFirstIndex() {
    Cell& cell0 = indexer[0];
    return cell0.occupied ? 0 : cell0.index;
}

template<typename T>
short PointlessMap<T>::getLastIndex() {
    Cell& cellEnd = indexer[end];
    return cellEnd.occupied ? end : cellEnd.index;
}

template<typename T>
bool PointlessMap<T>::contains(short index) {
    return indexer[index].occupied;
}

template<typename T>
bool PointlessMap<T>::isEmpty() {
    Cell& cell0 = indexer[0];
    return cell0.index==-1 && !cell0.occupied;
}

template class PointlessMap<char>; // char voor testing/debugging
template class PointlessMap<MapEndpoint>;
