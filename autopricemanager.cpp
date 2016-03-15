#include <QStandardItemModel>

#include "autopricemanager.h"
#include "serialize.h"

AutoPriceManager::AutoPriceManager(QString file, QStandardItemModel *model)
    : Model(model),
      File(file)
{
}

QDataStream &operator<<(QDataStream &out, const AutoPriceManager &s)
 {
    QVariantMap map;
    map["auto_price_list"] << s.AutoPriceList;
    out << map;

    return out;
 }

QDataStream &operator>>(QDataStream &in, AutoPriceManager &s)
 {
    QVariantMap map;
    in >> map;
    map["auto_price_list"] >> s.AutoPriceList;

    return in;
 }

