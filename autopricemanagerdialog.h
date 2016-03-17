#ifndef AUTOPRICEMANAGERDIALOG_H
#define AUTOPRICEMANAGERDIALOG_H

#include <QDialog>

class AutoPriceItemModel;
class AutoPriceDialog;

namespace Ui {
class AutoPriceManagerDialog;
}

class AutoPriceManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoPriceManagerDialog(QWidget *parent, AutoPriceItemModel *model);
    ~AutoPriceManagerDialog();

    Ui::AutoPriceManagerDialog *GetUi();

private:
    Ui::AutoPriceManagerDialog *ui;
    AutoPriceItemModel *model_;
    AutoPriceDialog *ap_dialog_;
};

#endif // AUTOPRICEMANAGERDIALOG_H
