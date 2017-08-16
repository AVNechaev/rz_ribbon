#include "ribbonapp.h"

#include "fireswsclient.h"
#include "notificator.h"
#include "ribbonwnd.h"
#include "ribbonmodel.h"

RibbonApp::RibbonApp(int argc, char **argv) :
    QApplication(argc, argv)
{    
    //cli = new FiresWSClient("930nyse.com", 8888, "nechaev.andrey@gmail.com", "123456");
    cli = new FiresWSClient("185.11.244.244", 8888, "nechaev.andrey@gmail.com", "123456");
    notificator = new Notificator(this);
    ribbon_data = new RibbonModel(RIBBON_DEPTH, this);
    ribbon_wnd = new RibbonWnd();
    ribbon_wnd->setModel(ribbon_data);

    connect(notificator, &Notificator::exitting, this, &QApplication::quit);
    connect(notificator, &Notificator::toggleRibbon, ribbon_wnd, &RibbonWnd::toggle);
    connect(cli, &FiresWSClient::gotMessage, notificator, &Notificator::on_fires_message);
    connect(cli, &FiresWSClient::gotMessage, ribbon_data, &RibbonModel::on_fire);
}

void RibbonApp::start()
{
    setApplicationDisplayName(tr("RZ Ribbon"));
    setApplicationName(tr("RZ Ribbon"));
    setWindowIcon(QIcon(":/images/trayicon.png"));
    setQuitOnLastWindowClosed(false);
    notificator->show();
}
