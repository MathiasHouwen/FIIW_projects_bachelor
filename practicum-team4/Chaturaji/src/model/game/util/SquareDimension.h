//practicum 3:
// - Ebbe: class gemaakt, copy paste van de oude Board class
// doel: logica ivm de range van het board ("ligt deze coordinaat binnen mijn bord?)"
//      decouplen van de board class

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
