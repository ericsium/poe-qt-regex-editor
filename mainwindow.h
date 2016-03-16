#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AutoPriceManagerDialog;
class AutoPriceManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionRegexp_Editor_triggered();


private:
    Ui::MainWindow *ui;
    AutoPriceManagerDialog *apm_dialog_;
    AutoPriceManager *apm_manager_;

};

#endif // MAINWINDOW_H
