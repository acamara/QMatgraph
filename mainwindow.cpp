#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_actions();
    create_graph_viewport();
}

MainWindow::~MainWindow()
{  
    delete plot;
    delete ui;
}

void MainWindow::create_actions(){

    saveAct = new QAction(QIcon(":/resources/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the graphs to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    zoom_inAct = new QAction(QIcon(":/resources/zoom_in.png"), tr("&zoom_in"), this);
    //zoom_inAct->setShortcuts(QKeySequence::New);
    zoom_inAct->setStatusTip(tr("Zoom in"));
    connect(zoom_inAct, SIGNAL(triggered()), this, SLOT(zoom_in()));

    zoom_outAct = new QAction(QIcon(":/resources/zoom_out.png"), tr("&zoom_out"), this);
    //zoom_outAct->setShortcuts(QKeySequence::Open);
    zoom_outAct->setStatusTip(tr("Zoom out"));
    connect(zoom_outAct, SIGNAL(triggered()), this, SLOT(zoom_out()));

    ui->mainToolBar->addAction(saveAct);
    ui->mainToolBar->addAction(zoom_outAct);
    ui->mainToolBar->addAction(zoom_inAct);
}

void MainWindow::create_graph_viewport(){
    plot = new QwtPlot();

    plot->setCanvasBackground(Qt::white);

    QwtPlotScaleItem *scaleItem = new QwtPlotScaleItem(QwtScaleDraw::RightScale, 0.0);
    scaleItem->attach(plot);
    plot->enableAxis(QwtPlot::yLeft, false);

    scaleItem = new QwtPlotScaleItem(QwtScaleDraw::BottomScale, 0.0);
    scaleItem->attach(plot);
    plot->enableAxis(QwtPlot::xBottom, false);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::black, 0, Qt::DotLine));
    grid->attach(plot);

    plot->setAxisScale(0,-20,20);
    plot->setAxisScale(2,-20,20);
    ui->centralWidget->layout()->addWidget(plot);

}

void MainWindow::save()
{

}

void MainWindow::zoom_in(){

}

void MainWindow::zoom_out(){

}

void MainWindow::interpret_expression(){
    signal = new QwtPlotCurve("Signal");

    static double fase= 0;
    fase+= 1;
    double *t;
    t = new double[1000];
    double *y;
    y = new double[1000];
    for (int i= 0; i < 1000; ++i) {
            t[i]= i;
            y[i]= 3 * sin (M_2_PI * 10.0 * t[i] + fase * M_PI / 10);
    }
    signal->setRawSamples(t, y, 1000);
    signal->attach(plot);
    plot->replot();
}
