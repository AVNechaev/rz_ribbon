#include "ribbonapp.h"

#include "fireswsclient.h"
#include "notificator.h"
#include "ribbonwnd.h"
#include "ribbonmodel.h"

RibbonApp::RibbonApp(int argc, char **argv) :
    QApplication(argc, argv)
{
    cli = new FiresWSClient("930nyse.com", 8888, "nechaev.andrey@gmail.com", "123456");
    notificator = new Notificator();
    ribbon_data = new RibbonModel(RIBBON_DEPTH);
    ribbon_wnd = new RibbonWnd();
    connect(notificator, &Notificator::exitting, this, &QApplication::quit);
    connect(notificator, &Notificator::toggleRibbon, ribbon_wnd, &RibbonWnd::toggle);
}

void RibbonApp::start()
{
    connect(cli, &FiresWSClient::gotMessage, notificator, &Notificator::on_fires_message);
    connect(cli, &FiresWSClient::gotMessage, ribbon_data, &RibbonModel::on_fire);

    notificator->show();
}
