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

    ui->listWidget_match->setProperty("match", true);
    ui->listWidget_mismatch->setProperty("match", false);

    ui->comboBox->addItems({"Orb of Alchemy","Chaos Orb", "Exalted Orb"});

    error_palette_.setColor(QPalette::Text,Qt::red);
    normal_palette_.setColor(QPalette::Text,Qt::black);
}

AutoPriceDialog::~AutoPriceDialog()
{
    delete ui;
}

void AutoPriceDialog::SetActiveExpression(QString str)
{
    active_expression_.setPattern(str);

}

void AutoPriceDialog::AddStringToListWidget(QString str, QListWidget *widget)
{
    auto item = new QListWidgetItem;
    item->setText(str);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    widget->addItem(item);
    UpdateListWidgetItemErrorState(item);
}

void AutoPriceDialog::LoadListWidgetFromRowColumn(QListWidget *widget, int row, int column)
{
    widget->clear();
    for (auto const &str: model_->item(row, column)->data(Qt::UserRole).toStringList()) {
        AddStringToListWidget(str, widget);
    }
}

void AutoPriceDialog::UpdateListWidgetErrorState(QListWidget *widget)
{
    for(int i = 0; i < widget->count(); ++i) {
        UpdateListWidgetItemErrorState(widget->item(i));
    }
}

void AutoPriceDialog::UpdateListWidgetItemErrorState(QListWidgetItem *item)
{
    QRegularExpression exp(ui->lineEdit->text());
    if (!exp.isValid()) return;

    QRegularExpressionMatch match = exp.match(item->text());
    // See if item matches
    if (item->listWidget()->property("match").toBool()) {
        item->setForeground(match.hasMatch() ? Qt::black : Qt::red);
            qDebug() << "Here I am match:" << ui->lineEdit->text() << " " << match.isValid() << " " << item->text();
    } else {
        item->setForeground(match.hasMatch() ? Qt::red : Qt::black);
            qDebug() << "Here I am mismatch:" << ui->lineEdit->text() << " "<< match.isValid() << " " << item->text();
    }
}

void AutoPriceDialog::OnIndexChanged(const QModelIndex &index)
{
    LoadListWidgetFromRowColumn(ui->listWidget_match, index.row(), 1);
    LoadListWidgetFromRowColumn(ui->listWidget_mismatch, index.row(), 2);

    mapper_->setCurrentModelIndex(index);
    current_row_ = index.row();
    exec();
}

void AutoPriceDialog::on_AutoPriceDialog_accepted()
{
    model_->itemFromIndex(model_->index(current_row_,1))->setData(Utils::items(ui->listWidget_match), Qt::UserRole);
    model_->itemFromIndex(model_->index(current_row_,2))->setData(Utils::items(ui->listWidget_mismatch), Qt::UserRole);
    mapper_->submit();
}

void AutoPriceDialog::on_lineEdit_textChanged(const QString &arg1)
{
    SetActiveExpression(arg1);

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
    UpdateListWidgetErrorState(ui->listWidget_match);
    UpdateListWidgetErrorState(ui->listWidget_mismatch);
}

void AutoPriceDialog::on_toolButton_match_remove_clicked()
{
    delete ui->listWidget_match->currentItem();
}

void AutoPriceDialog::on_toolButton_match_add_clicked()
{
    AddStringToListWidget("match_string", ui->listWidget_match);
}

void AutoPriceDialog::on_toolButton_mismatch_remove_clicked()
{
    delete ui->listWidget_mismatch->currentItem();
}

void AutoPriceDialog::on_toolButton_mismatch_add_clicked()
{
    AddStringToListWidget("mismatch_string", ui->listWidget_mismatch);
}

void AutoPriceDialog::on_listWidget_match_itemChanged(QListWidgetItem *item)
{
    UpdateListWidgetItemErrorState(item);
}
