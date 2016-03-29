#ifndef AUTOPRICEITEMMODEL_H
#define AUTOPRICEITEMMODEL_H

#include "autoprice.h"

#include <QAbstractTableModel>
#include <QObject>
#include <QVariant>

class AutoPriceItemModel : public QAbstractTableModel
{
public:
    class Column {
        regexp,
        currency_name,
        currency_value,
        has_value,
        enabled,
        matches,
        mismatches,
        COUNT
    };

public:
    AutoPriceItemModel(QObject *parent, QString file);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::UserRole + 1) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QString filename_;
    QVector<AutoPrice> auto_price_list_;


};

#endif // AUTOPRICEITEMMODEL_H
