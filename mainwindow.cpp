#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "autopricemanagerdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    APM_Dialog= new AutoPriceManagerDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRegexp_Editor_triggered()
{
    APM_Dialog->exec();
}
