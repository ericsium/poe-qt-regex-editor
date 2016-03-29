#include <QStandardItemModel>
#include <QFile>
#include <QDebug>

#include "autopricemanager.h"
#include "serialize.h"
#include "autopriceitemmodel.h"

const int g_magic_header_ = 0xF517DA8D;
const auto g_data_stream_ = QDataStream::Qt_4_7;

AutoPriceManager::AutoPriceManager(QString file, AutoPriceItemModel *model)
    : model_(model),
      filename_(file)
{
    qRegisterMetaTypeStreamOperators< QList<AutoPrice> >("QList<AutoPrice>");
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
        qDebug() << "Could not open '" << filename_ << "' for reading. File error: " << file.errorString();
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
        qDebug() << "Could not open '" << filename_ << "' for writing. File error: " << file.errorString();
    }

    return result;
}

void AutoPriceManager::LoadDefaultData()
{
    qDebug() << "LoadDefaultData()";
    AutoPrice item;
    item.expression_.setPattern(".*");
    auto_price_list_.append(std::move(item));
}

void AutoPriceManager::ReadFromModel()
{
    qDebug() << "ReadFromModel()";
    auto_price_list_.clear();

    /*
    for (auto row = 0; row < model_->rowCount(); row++) {
        AutoPrice tmp;
        for (auto column = 0; column < model_->columnCount(); column++) {
            QStandardItem *item = model_->item(row, column);
            switch(column) {
            case 0: tmp.expression_.setPattern(item->text()); break;
            case 1: tmp.matches = item->data().toStringList(); break;
            case 2: tmp.mismatches = item->data().toStringList(); break;
            }
        }
        auto_price_list_.append(std::move(tmp));
    }
    */
}

void AutoPriceManager::WriteToModel()
{
    qDebug() << "WriteToModel()";
    /*
    model_->clear();
    model_->setRowCount(auto_price_list_.size());
    model_->setColumnCount(3);

    int index = 0;
    for (AutoPrice const &ap: auto_price_list_) {
        auto item = new QStandardItem;
        item->setText(ap.expression_.pattern());
        model_->setItem(index,0,item);

        item = new QStandardItem;
        item->setData(ap.matches);
        model_->setItem(index,1,item);

        item = new QStandardItem;
        item->setData(ap.mismatches);
        model_->setItem(index,2,item);
        index++;
    }
    */
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

