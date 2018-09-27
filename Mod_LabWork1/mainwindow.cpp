#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qcustomplot.h"
#include "Logic/LehmerRand.h"
#include "Logic/ExpressCalculation.h"
#include "Logic/StandardCalculation.h"
#include "Logic/Testing.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    // Generate and calculate
    vector<double> xs;
    const uint32_t sampleSize = 1000000;

    double R = 0;
    double m = 0;
    double a = 0;
    if(ui->rLineEdit->text().isEmpty() || ui->aLineEdit->text().isEmpty() || ui->mLineEdit->text().isEmpty())
    {
        R = 4294965757;
        m = 4294967279;
        a = 2147483629;

    }
    else
    {
        R = ui->rLineEdit->text().toDouble();
        m = ui->mLineEdit->text().toDouble();
        a = ui->aLineEdit->text().toDouble();
    }

    LehmerRand lr(R, m, a);
    ExpressCalculation ec;

    for (uint32_t i = 0; i < sampleSize; i++)
    {
        double x = lr.Rand();
        ec.Input(x);
        xs.push_back(x);
    }

    ui->mExpressLabel->setText(QString::number(ec.m));
    ui->dExpressLabel->setText(QString::number(ec.D));
    ui->sigmaExpressLabel->setText(QString::number(ec.sd));
    ui->mStandardLabel->setText(QString::number(StandardCalculation::ExpectedValue(xs)));
    ui->dStandardLabel->setText(QString::number(StandardCalculation::Variance(xs)));
    ui->sigmaStandardLabel->setText(QString::number(StandardCalculation::StandardDeviation(xs)));

    // Testing
    Testing test;
    test.Inderect(xs);
    ui->indirectLabel->setText(QString::number(test.indirectResult));
    ui->piDiv4Label->setText(QString::number(test.piDiv4));

    LehmerRand lrTest(R, m, a);
    test.Aperiodic(lrTest);
    ui->PLabel->setText(QString::number(test.P));
    ui->LLabel->setText(QString::number(test.L));

    // Build histogram
    const uint32_t histogramSize = 20;
    double max = *max_element(xs.begin(), xs.end());
    double min = *min_element(xs.begin(), xs.end());
    double rVal = max - min;
    double delta = 1.0 / histogramSize;

    QVector<double> histogramData(histogramSize);


    for(uint32_t j = 0; j < xs.size(); j++)
    {
        for(int i = 0; i < histogramSize; i++)
        {
            double x = xs[j];
            if ((x> delta*i) && (x <= delta*(i+1)))
            {
                histogramData[i]++;
                break;
            }
        }
    }



    ui->histogram->clearPlottables();

    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->histogram->xAxis, ui->histogram->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    //regen->setStackingGap(1);
    // set names and colors:
    regen->setPen(QPen(QColor(0, 50, 140).lighter(0)));
    regen->setBrush(QColor(0, 70, 200, 50).lighter(130));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    for(int i = 1; i <= histogramSize; i++)
    {
        ticks << i;
        labels << QString::number(i);
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->histogram->xAxis->setTicker(textTicker);
    ui->histogram->xAxis->setSubTicks(false);
    ui->histogram->xAxis->setTickLength(0, 4);
    ui->histogram->xAxis->setBasePen(QPen(Qt::black));
    ui->histogram->xAxis->setTickPen(QPen(Qt::black));
    ui->histogram->xAxis->grid()->setVisible(true);
    ui->histogram->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->histogram->xAxis->setTickLabelColor(Qt::black);
    ui->histogram->xAxis->setLabelColor(Qt::black);

    // prepare y axis:
    ui->histogram->xAxis->setLabel("Histogram");
    ui->histogram->yAxis->setBasePen(QPen(Qt::black));
    ui->histogram->yAxis->setTickPen(QPen(Qt::black));
    ui->histogram->yAxis->setSubTickPen(QPen(Qt::black));
    ui->histogram->yAxis->grid()->setSubGridVisible(true);
    ui->histogram->yAxis->setTickLabelColor(Qt::black);
    ui->histogram->yAxis->setLabelColor(Qt::black);
    ui->histogram->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->histogram->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    regen->setData(ticks, histogramData);

    //ui->histogram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->histogram->rescaleAxes();
    ui->histogram->yAxis->setRangeUpper(ui->histogram->yAxis->range().upper*1.1);
    ui->histogram->xAxis->scaleRange(1.05);
    //ui->histogram->yAxis->setPadding(5); // a bit more space to the left border

    ui->histogram->replot();
}
