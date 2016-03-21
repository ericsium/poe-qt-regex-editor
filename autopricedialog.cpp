#include "autopricedialog.h"
#include "ui_autopricedialog.h"
#include "autopriceitemmodel.h"
#include "autopriceutils.h"
#include <QDataWidgetMapper>
#include <QDebug>
#include <QPushButton>

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

    error_palette_.setColor(QPalette::Text,Qt::red);
    normal_palette_.setColor(QPalette::Text,Qt::black);
}

AutoPriceDialog::~AutoPriceDialog()
{
    delete ui;
}

void AutoPriceDialog::OnIndexChanged(const QModelIndex &index)
{
    ui->listWidget_match->clear();
    ui->listWidget_match->addItems(model_->item(index.row(), 1)->data(Qt::UserRole).toStringList());

    ui->listWidget_mismatch->clear();
    ui->listWidget_mismatch->addItems(model_->item(index.row(), 2)->data(Qt::UserRole).toStringList());

    mapper_->setCurrentModelIndex(index);
    current_row_ = index.row();
    exec();
}

void AutoPriceDialog::on_AutoPriceDialog_accepted()
{
    QModelIndex a;
    a.
    model_->itemFromIndex(QModelIndex())
    model_->itemFromIndex()->setData(Utils::items(ui->listWidget_match), Qt::UserRole);
    model_->itemFromIndex(*current_index_)->setData(Utils::items(ui->listWidget_match), Qt::UserRole);

    mapper_->submit();
}

void AutoPriceDialog::on_lineEdit_textChanged(const QString &arg1)
{
    // Basically constantly evaluate regexp for validity
    QRegularExpression exp(arg1);
    if (!exp.isValid()) {
        ui->lineEdit->setPalette(error_palette_);
        ui->doubleSpinBox->setEnabled(false);
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
    } else {
        ui->lineEdit->setPalette(normal_palette_);
        ui->doubleSpinBox->setEnabled(exp.captureCount() == 0);
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( true );
    }
}

void AutoPriceDialog::on_toolButton_match_remove_clicked()
{
    delete ui->listWidget_match->currentItem();
}

void AutoPriceDialog::on_toolButton_match_add_clicked()
{
    auto const &widget = ui->listWidget_match;
    auto item = new QListWidgetItem;
    item->setText("match_string");
    widget->addItem(item);
}

void AutoPriceDialog::on_toolButton_mismatch_remove_clicked()
{
    delete ui->listWidget_mismatch->currentItem();
}

void AutoPriceDialog::on_toolButton_mismatch_add_clicked()
{
    auto const &widget = ui->listWidget_mismatch;
    auto item = new QListWidgetItem;
    item->setText("match_string");
    widget->addItem(item);
}
