#include "mainwindow.h"
#include <QApplication>
#include "fireswsclient.h"
#include "notificator.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);    
    FiresWSClient cli("addr", 8888, "user", "password");

    Notificator wnd;
    QObject::connect(&cli, &FiresWSClient::gotMessage, &wnd, &Notificator::on_fires_message);
    wnd.show();

    return a.exec();
}
