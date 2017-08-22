#include "ribbonapp.h"

#include "fireswsclient.h"
#include "notificator.h"
#include "ribbonwnd.h"
#include "ribbonmodel.h"
#include "logwriter.h"
#include "settings.h"

RibbonApp::RibbonApp(int argc, char **argv) :
    QApplication(argc, argv)
{    
    //cli = new FiresWSClient("930nyse.com", 8888, "nechaev.andrey@gmail.com", "123456");    
    cli = new FiresWSClient(this);
    notificator = new Notificator(this);
    ribbon_data = new RibbonModel(RIBBON_DEPTH, this);
    ribbon_wnd = new RibbonWnd();
    ribbon_wnd->setModel(ribbon_data);
    log_writer = new LogWriter(this);
    settings = new Settings(this);

    connect(notificator, &Notificator::exitting, this, &QApplication::quit);
    connect(notificator, &Notificator::toggleRibbon, ribbon_wnd, &RibbonWnd::toggle);
    connect(cli, &FiresWSClient::gotMessage, notificator, &Notificator::on_fires_message);
    connect(cli, &FiresWSClient::gotMessage, ribbon_data, &RibbonModel::on_fire);
    connect(cli, &FiresWSClient::gotMessage, log_writer, &LogWriter::on_fires_message);

    connect(settings, &Settings::changed, cli, &FiresWSClient::settings_changed);
    connect(settings, &Settings::changed, log_writer, &LogWriter::settings_changed);
    connect(settings, &Settings::changed, notificator, &Notificator::settings_changed);

    settings->setSettings(
                "nechaev.andrey@gmail.com",
                "123456",
                "185.11.244.244",
                8888,
                false,
                true,
                true,
                "./data.log");
}

void RibbonApp::start()
{
    setApplicationDisplayName(tr("RZ Ribbon"));
    setApplicationName(tr("RZ Ribbon"));
    setWindowIcon(QIcon(":/images/trayicon.png"));
    setQuitOnLastWindowClosed(false);
    notificator->show();
}
