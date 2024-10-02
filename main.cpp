#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color: #A0A0A0;");
    w.setWindowTitle("MP3 modifier");
    w.setFixedSize(800,600);
    w.show();
    return a.exec();
}
