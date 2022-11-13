#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workerthread.h"
#include <QDebug>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ZinkImage * zI;
    WorkerThread * wt;
    int selectedC;


private slots:
    void on_pushButtonStart_clicked();

    void finishedNewImg();
    void finishedAllImages();

    void on_spinBoxW_valueChanged(int arg1);

    void on_spinBoxH_valueChanged(int arg1);

    void on_spinBoxWachsttumsgeschwindigkeitRechts_valueChanged(int arg1);

    void on_spinBoxWachsttumsgeschwindigkeitLinks_valueChanged(int arg1);

    void on_spinBoxWachsttumsgeschwindigkeitOben_valueChanged(int arg1);

    void on_spinBoxWachsttumsgeschwindigkeitUnten_valueChanged(int arg1);

    void onStartC_clicked(int i);

private:
    Ui::MainWindow *ui;






    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};


#endif // MAINWINDOW_H
