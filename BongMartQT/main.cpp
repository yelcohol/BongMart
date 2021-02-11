#include "bongbong.h"
#include "Pos.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bongbong w;

    w.show();
    return a.exec();
}
