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

    void Load();
    void Save();

private:
    QVector<AutoPriceItem> AutoPriceList;
    QStandardItemModel *Model;
    QString File;
};

#endif // AUTOPRICEMANAGER_H
