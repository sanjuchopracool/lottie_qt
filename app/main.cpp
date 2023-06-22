#include <QApplication>

#include "AnimationWidget.h"
#include <QDir>

using namespace std;
using namespace eao;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    eao::AnimationViewWidget w;
    w.show();

    return a.exec();
}
