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
    void appendData(int data);

    QList<qreal> xList;
    QColor color[256];

private:
    Ui::ppi *ui;
};

#endif // PPI_H
