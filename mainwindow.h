#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_scaleitem.h>
#include <qwt_plot_grid.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void create_graph_viewport();
    void create_actions();
    void save();
    void zoom_in();
    void zoom_out();
    void interpret_expression();

private:
    Ui::MainWindow *ui;

    QwtPlot *plot;
    QwtPlotCurve *signal;

    QAction *saveAct;
    QAction *zoom_inAct;
    QAction *zoom_outAct;

};

#endif // MAINWINDOW_H
