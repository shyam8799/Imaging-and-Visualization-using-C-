#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow* w = new QMainWindow();

    MainWindow* mainWindow = new MainWindow();

    mainWindow->initialize();
    w->setCentralWidget(mainWindow);

    w->show();

    return a.exec();
}
