#ifndef CONSTANT_PROPERTY_H
#define CONSTANT_PROPERTY_H

#include "property.h"

namespace eao {

template<typename T>
class ConstantProperty : public Property<T>
{
public:
    using CRefValueType = const T &;
    ConstantProperty(T value)
        : m_value(std::move(value))
    {}

    ~ConstantProperty() override {}

    CRefValueType value() const { return m_value; }
    std::unique_ptr<PropertyAnimator<T>> create_animator(PropertyUpdateListener *) const override;

private:
    T m_value;
};

template<typename T>
class ConstantPropertyAnimator : public PropertyAnimator<T>
{
    using CRefProperty = const ConstantProperty<T> &;
    using CRefValueType = const T &;

public:
    ConstantPropertyAnimator(CRefValueType value)
        : m_value(value)
    {}
    ~ConstantPropertyAnimator() override {}
    void update(eao::FrameType frame) override {}
    CRefValueType value() const override { return m_value; }

private:
    const CRefValueType &m_value;
};

template<typename T>
std::unique_ptr<PropertyAnimator<T>> ConstantProperty<T>::create_animator(
    PropertyUpdateListener *) const
{
    return std::make_unique<ConstantPropertyAnimator<T>>(m_value);
}

} // namespace eao
#endif // CONSTANT_PROPERTY_H
