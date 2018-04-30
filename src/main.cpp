#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if(!w.ready)
    {
        qDebug() << "*** ready = " << w.ready;
        return 0;
    }

    return a.exec();
}
