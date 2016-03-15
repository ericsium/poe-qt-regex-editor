#include "autopricemanagerdialog.h"
#include "ui_autopricemanagerdialog.h"

AutoPriceManagerDialog::AutoPriceManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoPriceManagerDialog)
{
    ui->setupUi(this);
}

AutoPriceManagerDialog::~AutoPriceManagerDialog()
{
    delete ui;
}
