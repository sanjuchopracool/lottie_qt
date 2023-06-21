#ifndef KEYFRAMEGROUP_H
#define KEYFRAMEGROUP_H

#include "KeyFrame.h"

#include <QList>
#include <QJsonObject>
#include <QJsonArray>

namespace eao {

template<typename T>
class KeyFrameGroup
{
public:
    using KeyFrameType = KeyFrame<T>;

    ~KeyFrameGroup()
    {
    }

    void decode(const QJsonValue &in_value);

public:
    QList<KeyFrameType> m_keyframes;
};

struct DecoderHelper {
  template <typename T>
  static void do_decode(T& in_obj, const QJsonValue& in_value) {
    decode(in_obj, in_value);
  }
};

template<typename T>
void KeyFrameGroup<T>::decode(const QJsonValue &in_value)
{
    static const QString key_start("s");
    static const QString key_end("e");
    static const QString key_in_tan("i");
    static const QString key_out_tan("o");
    static const QString key_sp_in("ti");
    static const QString key_sp_out("to");
    static const QString key_hold("h");

    static const QString data_key = "k";
    QJsonValue value = in_value;
    QJsonObject obj = in_value.toObject();
    if (obj.contains(data_key))
    {
        value = obj.value(data_key);
    }
    if (value.isArray() and value.toArray().at(0).isObject() and value.toArray().at(0).toObject().contains("t"))
    {
        auto array = value.toArray();
        T prev_end_value;
        QVector2D prev_in_tangent;
        for (int i =0; i <array.count(); ++i)
        {
            auto object = array.at(i).toObject();
            T start_value;
            QVector2D in_tangent;
            QVector2D out_tangent;
            QVector3D sp_in_tan;
            QVector3D sp_out_tan;

            bool hold = false;

            FrameType time = object.value("t").toDouble();
            if (object.contains(key_start))
                DecoderHelper::do_decode<T>(start_value, object.value(key_start));
            else
                start_value = prev_end_value;

            if (object.contains(key_end))
                DecoderHelper::do_decode<T>(prev_end_value,object.value(key_end));

            if (object.contains(key_in_tan))
                eao::decode_keyframe_tangent(in_tangent, object.value(key_in_tan));

            if (object.contains(key_out_tan))
                eao::decode_keyframe_tangent(out_tangent, object.value(key_out_tan));

            if (object.contains(key_hold))
                hold = object.value(key_hold).toBool();

            if (object.contains(key_sp_in))
                eao::decode(sp_in_tan, object.value(key_sp_in));

            if (object.contains(key_sp_out))
                eao::decode(sp_out_tan, object.value(key_sp_out));

            m_keyframes.append(KeyFrameType(start_value, time, hold,
                                            prev_in_tangent, out_tangent,
                                            sp_in_tan, sp_out_tan));
            prev_in_tangent = in_tangent;
        }
    }
    else
    {
        T value_object;
        DecoderHelper::do_decode<T>(value_object, value);
        m_keyframes.append(KeyFrameType(value_object));
    }
}
}
#endif // KEYFRAMEGROUP_H
