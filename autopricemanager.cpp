#include <QStandardItemModel>
#include <QFile>
#include <QDebug>

#include "autopricemanager.h"
#include "serialize.h"

const int g_MagicHeader = 0xF517DA8D;

AutoPriceManager::AutoPriceManager(QString file, QStandardItemModel *model)
    : Model(model),
      Filename(file)
{
}

bool AutoPriceManager::Load()
{
    QFile file(Filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open '" << Filename << "'' for reading.";
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_7);

    int magicHeader;
    in >> magicHeader >> *this;
    file.close();
    return true;
}

bool AutoPriceManager::Save()
{
    QFile file(Filename);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open '" << Filename << "' for writing.";
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_7);

    out << g_MagicHeader << *this;
    file.close();
    return true;
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

