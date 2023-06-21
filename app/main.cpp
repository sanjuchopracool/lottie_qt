#include <QApplication>

#include "AnimationWidget.h"
#include <QDir>

using namespace std;
using namespace eao;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    eao::AnimationWidget w;
    w.load(QDir::homePath() + "/Downloads/15564-order-button-no-text.json");
//    w.load("/Users/sanjaychopra/TEMP/lottie-ios/Example/lottie-swift/TestAnimations/PinJump.json");
    w.show();

    return a.exec();
}
