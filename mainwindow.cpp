#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cameradialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_Camera_clicked()
{
    CameraDialog dialog;
    dialog.exec();
}
