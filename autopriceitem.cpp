#include <QVariantMap>
#include <QDataStream>

#include "autopriceitem.h"
#include "serialize.h"

QDataStream &operator<<(QDataStream &out, const AutoPriceItem &s)
 {
    QVariantMap map;
    map["expression"] << s.Expression;
    map["currency_name"] << s.CurrencyName;
    map["value"] << s.Value;
    map["has_value"] << s.HasValue;
    map["enabled"] << s.Enabled;
    out << map;

    return out;
 }

QDataStream &operator>>(QDataStream &in, AutoPriceItem &s)
 {
    QVariantMap map;

    in >> map;
    map["expression"] >> s.Expression;
    map["currency_name"] >> s.CurrencyName;
    map["value"] >> s.Value;
    map["has_value"] >> s.HasValue;
    map["enabled"] >> s.Enabled;

    return in;
 }
