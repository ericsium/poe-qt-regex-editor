#ifndef AUTOPRICEMANAGER_H
#define AUTOPRICEMANAGER_H

#include <QVector>
#include <QString>

#include "autoprice.h"

class QStandardItemModel;

class AutoPriceManager
{
public:
    AutoPriceManager(QString file, QStandardItemModel *model);

    bool Load();
    bool Save();

    void LoadDefaultData();

private:
    QList<AutoPrice> auto_price_list_;
    QStandardItemModel *model_;
    QString filename_;

    void ReadFromModel();
    void WriteToModel();

    // To support serialization of the class
    friend QDataStream &operator<<(QDataStream &out, const AutoPriceManager &s);
    friend QDataStream &operator>>(QDataStream &in, AutoPriceManager &s);
};

QDataStream &operator<<(QDataStream &out, const AutoPriceManager &s);
QDataStream &operator>>(QDataStream &in, AutoPrice &s);
#endif // AUTOPRICEMANAGER_H
