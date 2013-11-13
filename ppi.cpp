#include "ppi.h"
#include "ui_ppi.h"

ppi::ppi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ppi)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
    this->setFixedHeight(DIAMETER);
    this->setFixedWidth(DIAMETER);
    this->center.setX(DIAMETER/2);
    this->center.setY(DIAMETER/2);

    //init Scale
    this->radiusScale[0] = DIAMETER/2;    //radius
    this->radiusScale[1] = DIAMETER/2/5;  //radius*1/10
    this->radiusScale[2] = DIAMETER/5;    //radius*2/10
    this->radiusScale[3] = DIAMETER/2/5*3;//radius*3/10
    this->radiusScale[4] = DIAMETER/5*2;  //radius*4/10
    for (int i = 0; i < 6; i++) {
        this->angleScale[i*2].setX(DIAMETER/2-(DIAMETER/2*qCos(M_PI*i/6)));
        this->angleScale[i*2].setY(DIAMETER/2-(DIAMETER/2*qSin(M_PI*i/6)));
        this->angleScale[i*2+1].setX(DIAMETER/2+(DIAMETER/2*qCos(M_PI*i/6)));
        this->angleScale[i*2+1].setY(DIAMETER/2+(DIAMETER/2*qSin(M_PI*i/6)));
    }

    //init Points
    for (int j = 0; j < ANGLE_MAX; j++)
    {
        for (int i = 1; i <= RADIUS_MAX; i++)
        {
            this->points[j][i-1].setX(DIAMETER/2+DIAMETER/2*i/RADIUS_MAX*qSin(2*j*M_PI/ANGLE_MAX));
            this->points[j][i-1].setY(DIAMETER/2-DIAMETER/2*i/RADIUS_MAX*qCos(2*j*M_PI/ANGLE_MAX));
        }
    }

    //init Colormap
    QFile file("Jet256_Colormap.dat");
    if (!file.open(QIODevice::ReadOnly))
        qDebug()<<"WRONG FILE";
    QByteArray bytes = file.readAll();
    for (int i = 0; i < 256; i++)
        color[i].setRgb(static_cast<quint8>(bytes[i*3]), static_cast<quint8>(bytes[i*3+1]), static_cast<quint8>(bytes[i*3+2]));

    //init Timer
    QTimer *timer_input = new QTimer(this);
    connect(timer_input, SIGNAL(timeout()), this, SLOT(updateFrame()));
    timer_input->start(3);
}

ppi::~ppi()
{
    delete ui;
}

void ppi::updateFrame()
{
    static int i = 0;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec()+i);
    if (i>=ANGLE_MAX)
        i = 0;
    for (int j=0; j<RADIUS_MAX-1; j++)
        this->frame[i][j] = qrand() % 256;
    /*
    QPolygon poly(3);
    poly[0] = this->center;
    poly[1] = this->points[i][RADIUS_MAX];
    if (i+1==ANGLE_MAX)
        poly[2] = this->points[0][RADIUS_MAX];
    else
        poly[2] = this->points[i+1][RADIUS_MAX];
    poly[1] = QPoint(300, 500);
    poly[2] = QPoint(700, 700);
    QRegion r(poly);
    */
    if (i % 20 == 0) this->update();
    qDebug()<<"Update "<<i++;
}

void ppi::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    for (int j = 0; j < ANGLE_MAX; j++)
    {
        for (int i = 0; i < RADIUS_MAX-1; i++)
        {
            painter.setPen(QPen(this->color[this->frame[j][i]], 1));
            painter.setBrush(QBrush(this->color[this->frame[j][i]]));
            if (j+1 == ANGLE_MAX)
            {
                QPoint tmp[4] = {this->points[j][i], this->points[j][i+1], this->points[0][i+1], this->points[0][i]};
                painter.drawPolygon(tmp, 4);
            }
            else
            {
                QPoint tmp[4] = {this->points[j][i], this->points[j][i+1], this->points[j+1][i+1], this->points[j+1][i]};
                painter.drawPolygon(tmp, 4);
            }
        }
    }
    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(QPen(Qt::green, 4));
    painter.drawEllipse(this->center, this->radiusScale[0], this->radiusScale[0]);
    painter.setPen(QPen(Qt::green, 3));
    painter.drawEllipse(this->center, this->radiusScale[1], this->radiusScale[1]);
    painter.drawEllipse(this->center, this->radiusScale[2], this->radiusScale[2]);
    painter.drawEllipse(this->center, this->radiusScale[3], this->radiusScale[3]);
    painter.drawEllipse(this->center, this->radiusScale[4], this->radiusScale[4]);
    for (int i = 0; i < 6; i++) {
        painter.drawLine(this->angleScale[i*2], this->angleScale[i*2+1]);
    }
}
