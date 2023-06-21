#ifndef NODEPROPERTY_H
#define NODEPROPERTY_H

#include "AnyValueContainer.h"
#include "AnyValueProvider.h"

#include <QVariant>
#include <memory>

template <typename T>
class NodeProperty
{
public:
    using ValueType = T;
    using RefValueType = T&;
    using CRefValueType = const T&;
    using ValueProviderType = AnyValueProvider<T>;
    using ValueContainerType = AnyValueContainer<T>;


    NodeProperty( ValueProviderType* provider)
        : m_value_provider(provider)
    {

    }

    bool needs_update(eao::FrameType frame) const
    {
        return  m_value_container.needs_update() or m_value_provider->has_update(frame);
    }

    void update(eao::FrameType frame)
    {
        m_value_container.set_value(m_value_provider->value(frame), frame);
    }

    void set_provider(ValueProviderType* provider)
    {
        m_value_provider.reset(provider);
        m_value_container.set_needs_update();
    }

    bool is_static() const { return m_value_provider->is_static(); }

    CRefValueType value() const
    {
        return m_value_container.value();
    }
protected:
    std::unique_ptr<ValueProviderType> m_value_provider;
    ValueContainerType m_value_container;
};

using AnyNodeProperty = NodeProperty<QVariant>;
#endif // NODEPROPERTY_H
