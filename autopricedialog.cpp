#include "autopricedialog.h"
#include "ui_autopricedialog.h"
#include "autopriceitemmodel.h"
#include <QDataWidgetMapper>

AutoPriceDialog::AutoPriceDialog(QWidget *parent, AutoPriceItemModel *model) :
    QDialog(parent),
    ui(new Ui::AutoPriceDialog),
    model_(model),
    mapper_(new QDataWidgetMapper())
{
    ui->setupUi(this);
    mapper_->setModel(model_);
    mapper_->addMapping(ui->lineEdit, 0);
    mapper_->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    ui->comboBox->addItems({"Orb of Alchemy","Chaos Orb", "Exalted Orb"});
}

AutoPriceDialog::~AutoPriceDialog()
{
    delete ui;
}

void AutoPriceDialog::OnIndexChanged(const QModelIndex &index)
{
    mapper_->setCurrentModelIndex(index);
    exec();
}

void AutoPriceDialog::on_AutoPriceDialog_accepted()
{
    mapper_->submit();
}
