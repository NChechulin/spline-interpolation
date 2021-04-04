#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "spline.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFileButton_clicked()
{
    try {
        QFileInfo full_path(QFileDialog::getOpenFileName(this,  tr("Open file with points")));
        QString file_name = full_path.fileName();
        Spline s = Spline::FromFile(full_path.filePath());
        // if no exceptions were caught, we can change UI
        this->ui->fileLoadedStatusLabel->setText("Loaded " + file_name);
        this->full_path = full_path.filePath();
    }
    catch (std::exception& e) {
        QMessageBox msg;
        msg.setText(e.what());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}
