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
    QFileInfo full_path(QFileDialog::getOpenFileName(this,  tr("Open file with points")));
    QString file_name = full_path.fileName();
    this->ui->fileLoadedStatusLabel->setText("Loaded " + file_name);
    this->data_file_full_path = full_path.filePath();
}

void MainWindow::on_calculateInterpolationButton_clicked()
{
    try {
        this->spline = Spline::FromFile(this->data_file_full_path);
        std::vector<Polynome> polynomes = spline.Interpolate();
    } catch (std::exception& e) {
        QMessageBox msg;
        msg.setText(e.what());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}
