#include "autopriceitemmodel.h"

AutoPriceItemModel::AutoPriceItemModel(QObject *parent, QString filename)
    : QAbstractTableModel(parent),
      filename_(filename)
{

}

int AutoPriceItemModel::rowCount(const QModelIndex &parent) const
{
    return auto_price_list_.count();
}

int AutoPriceItemModel::columnCount(const QModelIndex &parent) const
{

}

QVariant AutoPriceItemModel::data(const QModelIndex &index, int role) const
{

}

QVariant AutoPriceItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

bool AutoPriceItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

Qt::ItemFlags AutoPriceItemModel::flags(const QModelIndex &index) const
{

}

bool AutoPriceItemModel::insertRows(int row, int count, const QModelIndex &parent)
{

}

bool AutoPriceItemModel::removeRows(int row, int count, const QModelIndex &parent)
{

}
