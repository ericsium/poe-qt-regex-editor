#include <QVariantMap>
#include <QDataStream>

#include "autoprice.h"
#include "serialize.h"

QDataStream &operator<<(QDataStream &out, const AutoPrice &s)
 {
    QVariantMap map;
    map["expression"] << s.expression_;
    map["currency_name"] << s.currency_name_;
    map["value"] << s.value_;
    map["has_value"] << s.has_value_;
    map["enabled"] << s.enabled_;
    map["matches"] << s.matches;
    map["mismatches"] << s.mismatches;
    out << map;

    return out;
 }

QDataStream &operator>>(QDataStream &in, AutoPrice &s)
 {
    QVariantMap map;
    in >> map;
    map["expression"] >> s.expression_;
    map["currency_name"] >> s.currency_name_;
    map["value"] >> s.value_;
    map["has_value"] >> s.has_value_;
    map["enabled"] >> s.enabled_;
    map["matches"] >> s.matches;
    map["mismatches"] >> s.mismatches;
    return in;
 }
