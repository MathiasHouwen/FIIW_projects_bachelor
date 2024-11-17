
#include <QApplication>
#include "view/startscreen/startscreen.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StartScreen s;
    s.show();
    return app.exec();
}