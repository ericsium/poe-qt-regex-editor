#ifndef AUTOPRICEMANAGERDIALOG_H
#define AUTOPRICEMANAGERDIALOG_H

#include <QDialog>

class QStandardItemModel;

namespace Ui {
class AutoPriceManagerDialog;
}

class AutoPriceManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoPriceManagerDialog(QWidget *parent = 0);
    ~AutoPriceManagerDialog();

    QStandardItemModel *GetModel() { return model_; };

private:
    Ui::AutoPriceManagerDialog *ui;
    QStandardItemModel *model_;
};

#endif // AUTOPRICEMANAGERDIALOG_H
