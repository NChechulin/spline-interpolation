#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "spline.h"

const double STEP = 1e-2;

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
        QVector<double> xs, ys;

        for (Polynome p : polynomes) {
            for (double x = p.from; x <= p.to; x += STEP) {
                xs.push_back(x);
                ys.push_back(p.GetValue(x));
            }
        }

        this->ui->customPlot->addGraph();
        this->ui->customPlot->graph(0)->setData(xs, ys);
        this->ui->customPlot->xAxis->setLabel("x");
        this->ui->customPlot->yAxis->setLabel("y");

        // pairs to set boundaries
        auto x_minmax = std::minmax_element(xs.begin(), xs.end());
        auto y_minmax = std::minmax_element(ys.begin(), ys.end());

        this->ui->customPlot->xAxis->setRange(*x_minmax.first - 1, *x_minmax.second + 1);
        this->ui->customPlot->yAxis->setRange(*y_minmax.first - 1, *y_minmax.second + 1);
        this->ui->customPlot->replot();

    } catch (std::exception& e) {
        QMessageBox msg;
        msg.setText(e.what());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}
