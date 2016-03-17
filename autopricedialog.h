#ifndef AUTOPRICEDIALOG_H
#define AUTOPRICEDIALOG_H

#include <QDialog>

namespace Ui {
class AutoPriceDialog;
}

class AutoPriceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoPriceDialog(QWidget *parent = 0);
    ~AutoPriceDialog();

private:
    Ui::AutoPriceDialog *ui;
};

#endif // AUTOPRICEDIALOG_H
