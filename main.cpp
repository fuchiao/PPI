#include "ppi.h"
#include <QApplication>
#include<QTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ppi w;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for (int i=0; i<256; i++) {
        for (int j=0; j<512; j++)
            w.frame[i][j] = qrand() % 256;
    }
    w.show();

    return a.exec();
}
