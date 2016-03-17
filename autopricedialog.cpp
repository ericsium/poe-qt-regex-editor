#include "autopricedialog.h"
#include "ui_autopricedialog.h"

AutoPriceDialog::AutoPriceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoPriceDialog)
{
    ui->setupUi(this);
}

AutoPriceDialog::~AutoPriceDialog()
{
    delete ui;
}
