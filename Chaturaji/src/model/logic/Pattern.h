//
// Created by ebbew on 11-10-2024.
//

#ifndef CHATURAJI_PATTERN_H
#define CHATURAJI_PATTERN_H

#include <QList>
#include <QPoint>
// volledig van ebbe
// NIET AANGEPAST IN PRACTICUM 2

/*
 *  Pattern is de move van een piece in 1 richting.
 *  Die zal later automatisch gedraaid worden voor alle 4 richtingen
 *
 * Een piece loopt [forward] cellen naar voor en [sideways] cellen opzij
 * sideways is een lijst want bvb paard kan 2 forward en -1 alsook 1 opzij (waardoor paard in totaal 8 bestemmingen heeft ipv 4)
 * Een pion loopt enkel (tov de spelers kant van het bord) rechtdoor -> =[forwardOnly]
 * Elke speler heeft dus wel een eigen richting die voor hem rechtdoor betekent -> [forwardDirection] (=eenheidsvector)
 * olifant kan "oneindig ver" (tot de rand van het bord) in een rechte lijn lopen -> = [infinite]
 *
 */

struct Pattern{
    int forward;
    QList<int> sideways;
    bool forwardOnly;
    bool infinite;
    QPoint forwardDirection;
};
#endif //CHATURAJI_PATTERN_H
