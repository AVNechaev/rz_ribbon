#include "ribbonapp.h"

#include "fireswsclient.h"
#include "notificator.h"

RibbonApp::RibbonApp(int argc, char **argv) :
    QApplication(argc, argv)
{
    cli = new FiresWSClient("930nyse.com", 8888, "nechaev.andrey@gmail.com", "123456");
    notificator = new Notificator();
    connect(notificator, &Notificator::exitting, this, &QApplication::quit);
}

void RibbonApp::start()
{
    QObject::connect(cli, &FiresWSClient::gotMessage, notificator, &Notificator::on_fires_message);
    notificator->show();
}
