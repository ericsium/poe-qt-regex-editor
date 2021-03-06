#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "autopricemanagerdialog.h"
#include "autopricemanager.h"
#include "autopriceitemmodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model_(new AutoPriceItemModel()),
    apm_dialog_(new AutoPriceManagerDialog(this, model_))
{
    ui->setupUi(this);
    apm_manager_ = new AutoPriceManager("testfile", model_);

    connect(apm_dialog_, &QDialog::accepted, [&]() {
        apm_manager_->Save();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRegexp_Editor_triggered()
{
    apm_manager_->Load();
    apm_dialog_->exec();
}
