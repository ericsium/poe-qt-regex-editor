#include "autopricemanagerdialog.h"
#include "ui_autopricemanagerdialog.h"
#include <QStandardItemModel>

AutoPriceManagerDialog::AutoPriceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoPriceManagerDialog),
    model_(new QStandardItemModel())

{
    ui->setupUi(this);
    ui->treeView->setModel(model_);
}

AutoPriceManagerDialog::~AutoPriceManagerDialog()
{
    delete ui;
}
