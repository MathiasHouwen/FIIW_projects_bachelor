// taakverdeling: zie h-file


#include "SquareDimension.h"

SquareDimension::SquareDimension(const int size) : size(size) {}

const int SquareDimension::getSize() const {
    return size;
}

bool SquareDimension::includes(const QPoint& coordinate) const {
    bool xInRange = coordinate.x() >= 0 && coordinate.x() <size;
    bool yInRange = coordinate.y() >= 0 && coordinate.y() <size;
    return xInRange && yInRange;
}
