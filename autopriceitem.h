#ifndef AUTOPRICEITEM_H
#define AUTOPRICEITEM_H

#include <QRegularExpression>
#include <QString>

class QDataStream;

class AutoPriceItem
{
public:
    QRegularExpression expression_;
    QString currency_name_;
    float value_{0.0};
    bool has_value_{false};
    bool enabled_{false};

    private:
    // To support serialization of the class
    friend QDataStream &operator<<(QDataStream &out, const AutoPriceItem &s);
    friend QDataStream &operator>>(QDataStream &in, AutoPriceItem &s);
};

Q_DECLARE_METATYPE(AutoPriceItem)

QDataStream &operator<<(QDataStream &out, const AutoPriceItem &s);
QDataStream &operator>>(QDataStream &in, AutoPriceItem &s);

#endif // AUTOPRICEITEM_H
