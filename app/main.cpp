#include "AnimationWidget.h"

#include <QApplication>
#include <third_party/minitrace/minitrace.h>

int main(int argc, char *argv[])
{
    mtr_init("trace.json");
    QApplication a(argc, argv);
    eao::AnimationViewWidget w;
    w.show();
    auto result =  a.exec();
    mtr_shutdown();
    return result;
}
