#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
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
    this->full_path = full_path.filePath();
    this->ui->fileLoadedStatusLabel->setText("Loaded " + file_name);

    Spline s = Spline::FromFile(this->full_path);
}
