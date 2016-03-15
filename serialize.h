#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "QVariant"

template<typename T>
void operator <<( QVariant& data, const T& target )
{
    data = QVariant::fromValue<T>( target );
}

template<typename T>
void operator >>( const QVariant& data, T& target )
{
    target = data.value<T>();
}

#endif // SERIALIZE_H
