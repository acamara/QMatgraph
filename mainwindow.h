#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <QWheelEvent>
#include <QList>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_scaleitem.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_scale_div.h>
#include <qwt_curve_fitter.h>


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

    void on_graphButton_clicked();
    void wheelEvent(QWheelEvent *event);

private:
    Ui::MainWindow *ui;

    enum {step_axis = 5, num_samples = 2000, max_zoom=1000 };
    int min_axis;
    int max_axis;

    QwtPlot *plot;
    QwtPlotCurve *signal;

    QAction *saveAct;
    QAction *zoom_inAct;
    QAction *zoom_outAct;

};

#endif // MAINWINDOW_H
