#include "mainwindow.h"
#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "using port " << argv[1] << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.SetupNetwork(atoi(argv[1]));
    return a.exec();
}
