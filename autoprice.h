#ifndef AUTOPRICE_H
#define AUTOPRICE_H

#include <QRegularExpression>
#include <QString>
#include <QStringList>

class QDataStream;

class AutoPrice
{
public:
    QRegularExpression expression_;
    QString currency_name_;
    float value_{0.0};
    bool has_value_{false};
    bool enabled_{false};
    QStringList matches;
    QStringList mismatches;

    private:
    // To support serialization of the class
    friend QDataStream &operator<<(QDataStream &out, const AutoPrice &s);
    friend QDataStream &operator>>(QDataStream &in, AutoPrice &s);
};

Q_DECLARE_METATYPE(AutoPrice)

QDataStream &operator<<(QDataStream &out, const AutoPrice &s);
QDataStream &operator>>(QDataStream &in, AutoPrice &s);

#endif // AUTOPRICE_H
