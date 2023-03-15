#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    writeToLog("Logging in");
    w.show();
    return a.exec();
}
