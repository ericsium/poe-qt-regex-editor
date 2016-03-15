#ifndef AUTOPRICEMANAGER_H
#define AUTOPRICEMANAGER_H

#include <QVector>
#include <QString>

#include "autopriceitem.h"

class QStandardItemModel;

class AutoPriceManager
{
public:
    AutoPriceManager(QString file, QStandardItemModel *model);

    bool Load();
    bool Save();

private:
    QList<AutoPriceItem> AutoPriceList;
    QStandardItemModel *Model;
    QString Filename;

    // To support serialization of the class
    friend QDataStream &operator<<(QDataStream &out, const AutoPriceManager &s);
    friend QDataStream &operator>>(QDataStream &in, AutoPriceManager &s);
};

QDataStream &operator<<(QDataStream &out, const AutoPriceManager &s);
QDataStream &operator>>(QDataStream &in, AutoPriceItem &s);
#endif // AUTOPRICEMANAGER_H
