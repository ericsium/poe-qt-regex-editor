#ifndef AUTOPRICEDIALOG_H
#define AUTOPRICEDIALOG_H

#include <QDialog>

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

public Q_SLOTS:
    void OnIndexChanged(const QModelIndex &index);
private slots:
    void on_AutoPriceDialog_accepted();
};

#endif // AUTOPRICEDIALOG_H
