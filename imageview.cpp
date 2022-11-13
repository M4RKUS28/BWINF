#include "imageview.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>


ImageView::ImageView(QWidget *parent)
    : QWidget{parent},
      zImg(nullptr)
{
    hdpi_scale = 1.0 / (double)this->devicePixelRatio();
}

void ImageView::setImage(ZinkImage *zI)
{
    this->zImg = zI;
    this->setFixedSize(zI->getSize());
}

void ImageView::paintEvent(QPaintEvent *)
{
    QPainter p(this);
//    p.begin(this);

    // wegen hdpi bildschirmen -> hoch auflösendere Bilder!
    if((double)this->devicePixelRatio() != 1)
        p.scale(hdpi_scale, hdpi_scale);

    // zeichne Bild
    if(zImg)
        p.drawImage(0,0, zImg->getImage());
    else
        p.fillRect(QRect(0, 0, this->width(), this->height()), Qt::white);

    p.setPen(QPen(Qt::blue));
    for( auto & e : startPoints)
        p.drawEllipse(e, 5, 5);


    p.setPen(QPen(Qt::blue, 3));
    p.drawPoints(startPoints.toVector().data(), startPoints.length());

    p.end();
}



void ImageView::mouseDoubleClickEvent(QMouseEvent *event)
{


}





void ImageView::mousePressEvent(QMouseEvent *event)
{
    for(int i  = 0;  i  < startPoints.length(); i++)
    if( (event->pos() - startPoints.at(i)).manhattanLength() <= 5 + 1) {
        qDebug() << event->pos() << " is old one";

        emit startClicked(i);

        return;
    }


    qDebug() << event->pos();
    startPoints.append(event->pos());
    if(zImg)
        zImg->addStartPoint(event->pos(), 2, 2, 2, 2, QColor::fromRgb(100, 100, 100));
    this->update();




}
