#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QObject>
#include <QWidget>

#include "zinkimage.h"


class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);

    void setImage(ZinkImage * zI);
    QList <QPoint> startPoints;

private:
    ZinkImage * zImg;
    double hdpi_scale;

//signals:


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};







#endif // IMAGEVIEW_H
