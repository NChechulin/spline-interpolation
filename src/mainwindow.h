#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include "interpolation.h"
#include <QFileDialog>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadFileButton_clicked();

    void on_calculateInterpolationButton_clicked();

private:
    Ui::MainWindow* ui;
    QString data_file_full_path;
    Interpolation spline;
    void SetupGraph();
    void PlotGraph(std::vector<Polynomial> polynomes);
    void PlotInputPoints(std::vector<QPoint> points);
    void Plot();
};
#endif // MAINWINDOW_H
