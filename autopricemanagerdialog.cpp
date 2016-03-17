#include "autopricemanagerdialog.h"
#include "ui_autopricemanagerdialog.h"
#include "autopriceitemmodel.h"
#include "autopricedialog.h"

AutoPriceManagerDialog::AutoPriceManagerDialog(QWidget *parent, AutoPriceItemModel *model) :
    QDialog(parent),
    ui(new Ui::AutoPriceManagerDialog),
    model_(model),
    ap_dialog_(new AutoPriceDialog(this, model_))

{
    ui->setupUi(this);
    ui->treeView->setModel(model_);

    connect(ui->treeView, &QTreeView::activated,
            ap_dialog_, &AutoPriceDialog::OnIndexChanged);

}

AutoPriceManagerDialog::~AutoPriceManagerDialog()
{
    delete ui;
}
