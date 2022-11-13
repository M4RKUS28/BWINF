#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wt = new WorkerThread();
    connect(wt, SIGNAL(finishedNewImg()), this, SLOT(finishedNewImg()));
    connect(wt, SIGNAL(finishedAllImages()), this, SLOT(finishedAllImages()));

    zI = nullptr;
    ui->widget->setFixedSize( QSize(ui->spinBoxW->value(), ui->spinBoxH->value()) );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete wt;
    if(zI)
        delete zI;
}


void MainWindow::on_pushButtonStart_clicked()
{
    if(wt->isRunning())
        return;
    else if(zI)
        delete zI;
    this->ui->pushButtonStart->setDisabled(true);

    zI = new ZinkImage(ui->spinBoxW->value(), ui->spinBoxH->value());
    ui->widget->setImage(zI);
    int i = 10;
    for(const auto & p : qAsConst(ui->widget->startPoints)) {
        i += 10;
        i %= 250;
        zI->addStartPoint(p, ui->spinBoxWachsttumsgeschwindigkeitUnten->value(), ui->spinBoxWachsttumsgeschwindigkeitOben->value(),
                          ui->spinBoxWachsttumsgeschwindigkeitRechts->value(), ui->spinBoxWachsttumsgeschwindigkeitLinks->value(),
                          QColor::fromRgb( i, i, i ) );
    }

//    zI->wR = ui->spinBoxWachsttumsgeschwindigkeitRechts->value();
//    zI->wL = ui->spinBoxWachsttumsgeschwindigkeitLinks->value();
//    zI->wO = ui->spinBoxWachsttumsgeschwindigkeitOben->value();
//    zI->wU = ui->spinBoxWachsttumsgeschwindigkeitUnten->value();

    wt->startThread(zI);
}

void MainWindow::finishedNewImg()
{
    ui->widget->update();
}

void MainWindow::finishedAllImages()
{
    this->ui->pushButtonStart->setDisabled(false);
}


void MainWindow::on_spinBoxW_valueChanged(int arg1)
{
    ui->widget->setFixedSize( QSize(ui->spinBoxW->value(), ui->spinBoxH->value()) );
}


void MainWindow::on_spinBoxH_valueChanged(int arg1)
{
    ui->widget->setFixedSize( QSize(ui->spinBoxW->value(), ui->spinBoxH->value()) );
}


void MainWindow::on_spinBoxWachsttumsgeschwindigkeitRechts_valueChanged(int arg1)
{
//    if(zI)
//    zI->wR = ui->spinBoxWachsttumsgeschwindigkeitRechts->value();
}


void MainWindow::on_spinBoxWachsttumsgeschwindigkeitLinks_valueChanged(int arg1)
{
//    if(zI)
//    zI->wL = ui->spinBoxWachsttumsgeschwindigkeitLinks->value();
}


void MainWindow::on_spinBoxWachsttumsgeschwindigkeitOben_valueChanged(int arg1)
{
//    if(zI)
//    zI->wO = ui->spinBoxWachsttumsgeschwindigkeitOben->value();
}


void MainWindow::on_spinBoxWachsttumsgeschwindigkeitUnten_valueChanged(int arg1)
{
//    if(zI)
//    zI->wU = ui->spinBoxWachsttumsgeschwindigkeitUnten->value();
}

