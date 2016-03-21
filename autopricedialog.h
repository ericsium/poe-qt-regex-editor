#ifndef AUTOPRICEDIALOG_H
#define AUTOPRICEDIALOG_H

#include <QDialog>
#include <QPalette>

class AutoPriceItemModel;
class QDataWidgetMapper;
class QModelIndex;

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
    QModelIndex const *current_index_;

public Q_SLOTS:
    void OnIndexChanged(const QModelIndex &index);
private slots:
    void on_AutoPriceDialog_accepted();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_toolButton_match_remove_clicked();
    void on_toolButton_match_add_clicked();
    void on_toolButton_mismatch_remove_clicked();
    void on_toolButton_mismatch_add_clicked();
};

#endif // AUTOPRICEDIALOG_H
