#include "ppi.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ppi w;
    w.show();

    return a.exec();
}
