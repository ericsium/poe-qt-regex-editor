#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AutoPriceManagerDialog;

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
    AutoPriceManagerDialog *APM_Dialog;

};

#endif // MAINWINDOW_H
