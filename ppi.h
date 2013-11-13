#ifndef PPI_H
#define PPI_H

#include <QWidget>

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

    quint8 frame[256][512]; //angle, distance
    QColor color[256];

private slots:
    void updateFrame();

private:
    Ui::ppi *ui;
};

#endif // PPI_H
