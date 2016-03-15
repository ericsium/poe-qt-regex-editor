#ifndef AUTOPRICEMANAGERDIALOG_H
#define AUTOPRICEMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class AutoPriceManagerDialog;
}

class AutoPriceManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoPriceManagerDialog(QWidget *parent = 0);
    ~AutoPriceManagerDialog();

private:
    Ui::AutoPriceManagerDialog *ui;
};

#endif // AUTOPRICEMANAGERDIALOG_H
