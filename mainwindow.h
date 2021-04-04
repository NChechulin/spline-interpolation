#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "qcustomplot.h"
#include "spline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadFileButton_clicked();

    void on_calculateInterpolationButton_clicked();

private:
    Ui::MainWindow *ui;
    QString data_file_full_path;
    Spline spline;
    void SetupGraph();
    void PlotGraph(std::vector<Polynome> polynomes);
    void PlotInputPoints(std::vector<QPoint> points);
    void Plot();
};
#endif // MAINWINDOW_H
