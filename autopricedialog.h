#ifndef AUTOPRICEDIALOG_H
#define AUTOPRICEDIALOG_H

#include <QDialog>
#include <QPalette>
#include <QRegularExpression>

class AutoPriceItemModel;
class QDataWidgetMapper;
class QModelIndex;
class QListWidget;
class QListWidgetItem;

namespace Ui {
class AutoPriceDialog;
}

class AutoPriceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoPriceDialog(QWidget *parent, AutoPriceItemModel *model);
    ~AutoPriceDialog();
    QDataWidgetMapper *GetMapper() { return mapper_;}

private:
    Ui::AutoPriceDialog *ui;
    AutoPriceItemModel *model_;
    QDataWidgetMapper *mapper_;
    QPalette error_palette_;
    QPalette normal_palette_;
    int current_row_;
    QRegularExpression active_expression_;

    void SetActiveExpression(QString str);
    void AddStringToListWidget(QString str, QListWidget *widget);
    void LoadListWidgetFromRowColumn(QListWidget *widget, int row, int column);
    void UpdateListWidgetErrorState(QListWidget *widget);
    void UpdateListWidgetItemErrorState(QListWidgetItem *item);

    int ErrorCount() const;
    int ListWidgetErrorCount(QListWidget *widget) const;

public Q_SLOTS:
    void OnIndexChanged(const QModelIndex &index);
private slots:
    void on_AutoPriceDialog_accepted();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_toolButton_match_remove_clicked();
    void on_toolButton_match_add_clicked();
    void on_toolButton_mismatch_remove_clicked();
    void on_toolButton_mismatch_add_clicked();
    void on_listWidget_match_itemChanged(QListWidgetItem *item);
    void on_listWidget_mismatch_itemChanged(QListWidgetItem *item);
    void on_buttonBox_accepted();
};

#endif // AUTOPRICEDIALOG_H
