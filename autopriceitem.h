#ifndef AUTOPRICEITEM_H
#define AUTOPRICEITEM_H

#include <QRegularExpression>
#include <QString>

class QDataStream;
class AutoPriceItem
{
public:
    AutoPriceItem() = default;

private:
    QRegularExpression Expression;
    QString CurrencyName;
    float Value{0.0};
    bool HasValue{false};
    bool Enabled{false};

    // To support serialization of the class
    friend QDataStream &operator<<(QDataStream &out, const AutoPriceItem &s);
    friend QDataStream &operator>>(QDataStream &in, AutoPriceItem &s);
};

Q_DECLARE_METATYPE(AutoPriceItem)

QDataStream &operator<<(QDataStream &out, const AutoPriceItem &s);
QDataStream &operator>>(QDataStream &in, AutoPriceItem &s);

#endif // AUTOPRICEITEM_H
