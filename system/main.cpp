#include "mainwindow.h"
#include <QApplication>
#include "globle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    MainWindow w;
    w.show();
    return a.exec();
}
