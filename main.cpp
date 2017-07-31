#include "mainwindow.h"
#include <QApplication>
#include "fireswsclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    FiresWSClient cli("addr", 8888, "user", "password");

    return a.exec();
}
