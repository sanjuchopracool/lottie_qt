#ifndef MERGE_H
#define MERGE_H

#include "ShapeItem.h"

namespace eao {

enum class MergeMode {
      None,
      Merge,
      Add,
      Subtract,
      Intersect,
      Exclude
};

class Merge : public ShapeItem
{
public:
    Merge();

    virtual void decode(const QJsonObject& in_obj) override;

private:
    MergeMode m_mode = MergeMode::None;
    QString m_name;
    QString m_match_name;
};
}

#endif // MERGE_H
