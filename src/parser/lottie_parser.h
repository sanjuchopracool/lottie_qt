#ifndef LOTTIEPARSER_H
#define LOTTIEPARSER_H

#include <QStringList>

class QJsonObject;

namespace eao {
class Composition;
}

namespace eao::Lottie {

class LottieParser
{
public:
    static std::unique_ptr<Composition> parse(const QJsonObject &in_obj, QStringList &out_messages);
};

} // namespace eao::Lottie

#endif // LOTTIEPARSER_H
