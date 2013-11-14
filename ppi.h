#ifndef PPI_H
#define PPI_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
namespace Ui {
class ppi;
}

class ppi : public QWidget
{
    Q_OBJECT

public:
    explicit ppi(QWidget *parent = 0);
    ~ppi();
    void paintEvent(QPaintEvent *);
#define ANGLE_MAX 512
#define RADIUS_MAX 512
    quint8 frame[ANGLE_MAX][RADIUS_MAX]; //angle, radius
    QColor color[256];
#define DIAMETER 800
    QPoint points[ANGLE_MAX][RADIUS_MAX];
    QPoint center;
    int radiusScale[5];
    QPoint angleScale[12];
    int index;

private slots:
    void updateFrame();

private:
    Ui::ppi *ui;
};

#endif // PPI_H
