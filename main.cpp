#include "mainwindow.h"
#include "signup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // Signup w;
    w.show();
    return a.exec();
}
