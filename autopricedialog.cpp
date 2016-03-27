#include "autopricedialog.h"
#include "ui_autopricedialog.h"
#include "autopriceitemmodel.h"
#include <QDataWidgetMapper>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>

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
    for (auto const &str: model_->item(row, column)->data().toStringList()) {
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
    } else {
        item->setForeground(match.hasMatch() ? Qt::red : Qt::black);
    }
}

QStringList AutoPriceDialog::ListWidgetToStringList(const QListWidget *widget)
{
    QStringList tmp;
    for (auto row = 0; row < widget->count(); row++) {
        tmp.push_back(widget->item(row)->text());
    }
    return tmp;
}

int AutoPriceDialog::ErrorCount() const
{
    int error_count{0};
    if (!active_expression_.isValid()) { ++error_count; };
    error_count += ListWidgetErrorCount(ui->listWidget_match);
    error_count += ListWidgetErrorCount(ui->listWidget_mismatch);
    return error_count;
}

int AutoPriceDialog::ListWidgetErrorCount(QListWidget *widget) const
{
    int error_count{0};
    for(int i = 0; i < widget->count(); ++i) {
        QListWidgetItem *item = widget->item(i);
        if (item->foreground() == Qt::red) {++error_count;}
    }
    return error_count;
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
    model_->itemFromIndex(model_->index(current_row_,1))->setData(ListWidgetToStringList(ui->listWidget_match));
    model_->itemFromIndex(model_->index(current_row_,2))->setData(ListWidgetToStringList(ui->listWidget_mismatch));
    mapper_->submit();
}

void AutoPriceDialog::on_lineEdit_textChanged(const QString &arg1)
{
    SetActiveExpression(arg1);

    // Basically constantly evaluate regexp for validity
    if (!active_expression_.isValid()) {
        ui->lineEdit->setPalette(error_palette_);
        ui->doubleSpinBox->setEnabled(false);
    } else {
        ui->lineEdit->setPalette(normal_palette_);
        ui->doubleSpinBox->setEnabled(active_expression_.captureCount() == 0);
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

void AutoPriceDialog::on_listWidget_mismatch_itemChanged(QListWidgetItem *item)
{
    UpdateListWidgetItemErrorState(item);
}

void AutoPriceDialog::on_buttonBox_accepted()
{
    if (ErrorCount() == 0 ) {
        accept();
    } else {
        QMessageBox::warning(this, "Error", QString("You have ") + QString::number(ErrorCount()) + " active errors (in red) that you must fix before submitting.");
    }
}
