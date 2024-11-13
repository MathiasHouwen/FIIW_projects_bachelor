//
// Created by ebbew on 13-11-2024.
//

#ifndef CHATURAJI_DIEVIEW_H
#define CHATURAJI_DIEVIEW_H


#include <QWidget>
#include <QSvgWidget>
#include <QDomDocument>

class DieView : public QWidget{
Q_OBJECT
private:
    static inline QSet<QString> svgToggleGroups[6] = {
            {"m"},
            {"d1"},
            {"d1", "m"},
            {"d1", "d2"},
            {"d1", "d2", "m"},
            {"d1", "d2", "h"}
    };
    QSvgWidget* svg;
    QDomDocument svgDOM;

public:
    DieView(QWidget* parent, int number);
    void updateNumber(int number);
    void updateDisabled(bool disabled);
};


#endif //CHATURAJI_DIEVIEW_H
