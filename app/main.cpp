#include "AnimationWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eao::AnimationViewWidget w;
    w.show();

    return a.exec();
}
