#ifndef AUTOPRICEITEM_H
#define AUTOPRICEITEM_H

#include <QRegularExpression>
#include <QString>

class AutoPriceItem
{
public:
    AutoPriceItem();

private:
    QRegularExpression Expression;
    QString CurrencyName;
    float Value;
    bool HasValue;
    bool Enabled;
};

#endif // AUTOPRICEITEM_H
