#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

#include "interpreter/parser.h"

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
    max_axis = 20;
    min_axis = -20;

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

    QwtPlotPicker* picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand,
                                              QwtPicker::ActiveOnly, plot->canvas());
    picker->setStateMachine(new QwtPickerDragPointMachine());
    picker->setRubberBandPen(QColor(Qt::darkMagenta));
    picker->setRubberBand(QwtPicker::CrossRubberBand);
    picker->setTrackerPen(QColor(Qt::green));

    plot->setAxisScale(0,min_axis,max_axis);
    plot->setAxisScale(2,min_axis,max_axis);
    ui->centralWidget->layout()->addWidget(plot);
    connect(ui->expression_lineEdit, SIGNAL(returnPressed()),ui->graphButton,SIGNAL(clicked()));

}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"), QString(),"Graphic files (*.png  )");

    if ( !fileName.isEmpty() ){
        QImage image( QSize(800,600), QImage::Format_ARGB32 );
        image.fill(QColor(Qt::white).rgba());
        QPainter painter(&image);

        QwtPlotRenderer renderer;
        renderer.render(plot, &painter, image.rect());
        painter.end();
        image.save(fileName, 0, 0);
    }
}

void MainWindow::zoom_in(){
    if(max_axis > step_axis){
        min_axis = min_axis + step_axis;
        max_axis = max_axis - step_axis;
        plot->setAxisScale(0,min_axis,max_axis);
        plot->setAxisScale(2,min_axis,max_axis);
        plot->replot();
    }
}

void MainWindow::zoom_out(){
    if(max_axis < max_zoom){
        min_axis = min_axis - step_axis;
        max_axis = max_axis + step_axis;
        plot->setAxisScale(0,min_axis,max_axis);
        plot->setAxisScale(2,min_axis,max_axis);
        plot->replot();
    }
}

void MainWindow::interpret_expression(){
    signal = new QwtPlotCurve("Signal");
    double *signalx;
    signalx = new double[num_samples];
    double *signaly;
    signaly = new double[num_samples];

    // create a parser object
    Parser prs;

    QString expr = ui->expression_lineEdit->text();

    if(expr.contains("=")){
        expr = expr.remove(0, expr.indexOf("=")+1);
    }

    int i=0;
    for (int x = ((num_samples/2)*(-1)); x < (num_samples/2); x++) {
            QString var = "x="+QString::number(x);
            prs.parse(var.toStdString().c_str());

            // evaluate the expression
            signalx[i]= x;
            signaly[i]= prs.parse(expr.toStdString().c_str());;
            i++;
    }

    signal->setRawSamples(signalx, signaly, num_samples);
    signal->attach(plot);
    plot->replot();
}

void MainWindow::on_graphButton_clicked()
{
    interpret_expression();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        //qDebug()<<"Mouse event arriba";
        zoom_in();
    }
    else{
        //qDebug()<<"Mouse event abajo";
        zoom_out();
    }
}
