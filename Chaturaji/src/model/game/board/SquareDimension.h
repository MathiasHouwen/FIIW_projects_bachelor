//
// Created by ebbew on 3-1-2025.
//

#ifndef CHATURAJI_SQUAREDIMENSION_H
#define CHATURAJI_SQUAREDIMENSION_H


#include <QPoint>

class SquareDimension {
private:
    const int size;
public:
    explicit SquareDimension(const int size);
    [[nodiscard]] const int getSize() const;
    bool includes(const QPoint& coordinate) const; // kijkt of een coordinaat binnen de dimensie ligt
};


#endif //CHATURAJI_SQUAREDIMENSION_H
