#include "ppi.h"
#include "ui_ppi.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QFile>
ppi::ppi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ppi)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
    this->setFixedHeight(800);
    this->setFixedWidth(800);
    QFile file("Jet256_Colormap.dat");
    if (!file.open(QIODevice::ReadOnly))
        qDebug()<<"WRONG FILE";
    QByteArray bytes = file.readAll();
    for (int i = 0; i < 256; i++)
        color[i].setRgb(static_cast<quint8>(bytes[i*3]), static_cast<quint8>(bytes[i*3+1]), static_cast<quint8>(bytes[i*3+2]));
}

ppi::~ppi()
{
    delete ui;
}

void ppi::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int diameter = 800;
    QPoint center(diameter/2, diameter/2);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(center, diameter/2, diameter/2);
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawEllipse(center, diameter/10, diameter/10);
    painter.drawEllipse(center, diameter*2/10, diameter*2/10);
    painter.drawEllipse(center, diameter*3/10, diameter*3/10);
    painter.drawEllipse(center, diameter*4/10, diameter*4/10);
    for (int i = 0; i < 6; i+=1) {
        QPoint tmp1, tmp2;
        tmp1.setX(center.x()-(diameter/2*qCos(M_PI*i/6)));
        tmp1.setY(center.x()-(diameter/2*qSin(M_PI*i/6)));
        tmp2.setX(center.x()+(diameter/2*qCos(M_PI*i/6)));
        tmp2.setY(center.x()+(diameter/2*qSin(M_PI*i/6)));
        painter.drawLine(tmp1, tmp2);
    }
    QPointF points[4];
    int radius = 512;
    int theta = 256;
    int j = 10;
    j -= theta/4;   //oriented by north
    j *= -1;    //transform to clockwise
    for (int i = 1; i <= radius; i++)
    {
        if (i%2==0) {
        painter.setPen(QPen(this->color[132], 0));
        painter.setBrush(QBrush(this->color[132]));
        }
        else {
            painter.setPen(QPen(this->color[13], 0));
            painter.setBrush(QBrush(this->color[13]));
        }

        points[0].setX(diameter/2+diameter/2*i/radius*qCos(2*j*M_PI/theta));
        points[0].setY(diameter/2-diameter/2*i/radius*qSin(2*j*M_PI/theta));
        points[1].setX(diameter/2+diameter/2*(i-1)/radius*qCos(2*j*M_PI/theta));
        points[1].setY(diameter/2-diameter/2*(i-1)/radius*qSin(2*j*M_PI/theta));
        points[3].setX(diameter/2+diameter/2*i/radius*qCos(2*(j+1)*M_PI/theta));
        points[3].setY(diameter/2-diameter/2*i/radius*qSin(2*(j+1)*M_PI/theta));
        points[2].setX(diameter/2+diameter/2*(i-1)/radius*qCos(2*(j+1)*M_PI/theta));
        points[2].setY(diameter/2-diameter/2*(i-1)/radius*qSin(2*(j+1)*M_PI/theta));
        painter.drawPolygon(points, 4);
    }
}
