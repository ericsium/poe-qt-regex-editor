#include <QStandardItemModel>
#include <QFile>
#include <QDebug>

#include "autopricemanager.h"
#include "serialize.h"

const int g_magic_header_ = 0xF517DA8D;
const auto g_data_stream_ = QDataStream::Qt_4_7;

AutoPriceManager::AutoPriceManager(QString file, QStandardItemModel *model)
    : model_(model),
      filename_(file)
{
    qRegisterMetaTypeStreamOperators<QList<AutoPriceItem>>("QList<AutoPriceItem>");
    Load();
}

bool AutoPriceManager::Load()
{
    bool result = false;

    qDebug() << "Load()";
    QFile file(filename_);

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in.setVersion(g_data_stream_);

        int magicHeader;
        in >> magicHeader;
        if (magicHeader == g_magic_header_) {
            in >> *this;
            result = true;
        } else {
            qDebug() << "Magic header mistmach.  File '" << filename_ << "' does not look like a valid input file.";
        }
        file.close();
    } else {
         qDebug() << "Could not open '" << filename_ << "'' for reading.";
    }

    if (auto_price_list_.empty())
        LoadDefaultData();

    WriteToModel();

    return result;
}

bool AutoPriceManager::Save()
{
    bool result = false;

    qDebug() << "Save()";
    QFile file(filename_);

    ReadFromModel();

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out.setVersion(g_data_stream_);

        out << g_magic_header_ << *this;
        file.close();
        result = false;
    } else {
        qDebug() << "Could not open '" << filename_ << "' for writing.";
    }

    return result;
}

void AutoPriceManager::LoadDefaultData()
{
    qDebug() << "LoadDefaultData()";
    AutoPriceItem item;
    item.expression_.setPattern(".*");
    auto_price_list_.append(std::move(item));
}

//
void AutoPriceManager::ReadFromModel()
{
    qDebug() << "ReadFromModel()";
    auto_price_list_.clear();
    for (QStandardItem *item: model_->takeColumn(0)) {
        AutoPriceItem tmp;
        tmp.expression_.setPattern(item->text());
        auto_price_list_.append(std::move(tmp));
    }
}

void AutoPriceManager::WriteToModel()
{
    qDebug() << "WriteToModel()";
    model_->clear();
    model_->setRowCount(auto_price_list_.size());
    model_->setColumnCount(1);

    int index = 0;
    for (AutoPriceItem const &ap: auto_price_list_) {
        auto item = new QStandardItem;
        item->setText(ap.expression_.pattern());
        qDebug() << ap.expression_.pattern();
        model_->setItem(index++,0,item);
    }
}


QDataStream &operator<<(QDataStream &out, const AutoPriceManager &s)
{
    QVariantMap map;
    map["auto_price_list"] << s.auto_price_list_;
    out << map;

    return out;
}

QDataStream &operator>>(QDataStream &in, AutoPriceManager &s)
{
    QVariantMap map;
    in >> map;
    map["auto_price_list"] >> s.auto_price_list_;

    return in;
}

