#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "interpolation.h"
#include "ui_mainwindow.h"

const double STEP = 1e-2;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetupGraph() {
  // for splines
  this->ui->customPlot->addGraph();
  // for points
  this->ui->customPlot->addGraph();
  this->ui->customPlot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
  this->ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  this->ui->customPlot->graph(1)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  // labels
  this->ui->customPlot->xAxis->setLabel("x");
  this->ui->customPlot->yAxis->setLabel("y");
}

void MainWindow::PlotGraph(std::vector<Polynomial> polynomes) {
  QVector<double> xs, ys;

  for (Polynomial p : polynomes) {
    for (double x = p.from; x <= p.to; x += STEP) {
      xs.push_back(x);
      ys.push_back(p.GetValue(x));
    }
  }

  this->ui->customPlot->graph(0)->setData(xs, ys);

  // pairs to set boundaries
  auto x_minmax = std::minmax_element(xs.begin(), xs.end());
  auto y_minmax = std::minmax_element(ys.begin(), ys.end());

  this->ui->customPlot->xAxis->setRange(*x_minmax.first - 1,
                                        *x_minmax.second + 1);
  this->ui->customPlot->yAxis->setRange(*y_minmax.first - 1,
                                        *y_minmax.second + 1);
}

void MainWindow::PlotInputPoints(std::vector<QPoint> points) {
  QVector<double> xs, ys;
  for (QPoint p : points) {
    xs.push_back(p.x());
    ys.push_back(p.y());
  }

  this->ui->customPlot->graph(1)->setData(xs, ys);
}

void MainWindow::Plot() {
  SetupGraph();
  PlotGraph(this->spline.Interpolate());
  PlotInputPoints(this->spline.points);
  this->ui->customPlot->replot();
}

void MainWindow::on_loadFileButton_clicked() {
  QFileInfo full_path(
      QFileDialog::getOpenFileName(this, tr("Open file with points")));
  QString file_name = full_path.fileName();
  this->ui->fileLoadedStatusLabel->setText("Loaded " + file_name);
  this->data_file_full_path = full_path.filePath();
}

void MainWindow::on_calculateInterpolationButton_clicked() {
  try {
    this->spline = Interpolation::FromFile(this->data_file_full_path);
    Plot();
  } catch (std::exception& e) {
    QMessageBox msg;
    msg.setText(e.what());
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();
  }
}
