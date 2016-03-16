#include <QVariantMap>
#include <QDataStream>

#include "autopriceitem.h"
#include "serialize.h"

QDataStream &operator<<(QDataStream &out, const AutoPriceItem &s)
 {
    QVariantMap map;
    map["expression"] << s.expression_;
    map["currency_name"] << s.currency_name_;
    map["value"] << s.value_;
    map["has_value"] << s.has_value_;
    map["enabled"] << s.enabled_;
    out << map;

    return out;
 }

QDataStream &operator>>(QDataStream &in, AutoPriceItem &s)
 {
    QVariantMap map;

    in >> map;
    map["expression"] >> s.expression_;
    map["currency_name"] >> s.currency_name_;
    map["value"] >> s.value_;
    map["has_value"] >> s.has_value_;
    map["enabled"] >> s.enabled_;

    return in;
 }
