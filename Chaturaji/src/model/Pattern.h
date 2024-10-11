//
// Created by ebbew on 11-10-2024.
//

#ifndef CHATURAJI_PATTERN_H
#define CHATURAJI_PATTERN_H

#include <QList>
#include <QPoint>

struct Pattern{
    int forward;
    QList<int> sideways;
    bool forwardOnly;
    bool infinite;
    QPoint forwardDirection;
};
#endif //CHATURAJI_PATTERN_H
