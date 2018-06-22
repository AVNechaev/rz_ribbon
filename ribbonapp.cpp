#include "ribbonapp.h"

#include "fireswsclient.h"
#include "notificator.h"
#include "ribbonwnd.h"
#include "ribbonmodel.h"
#include "logwriter.h"
#include "settings.h"
#include "settingswindow.h"

#include <QStandardPaths>
#include <QDir>

RibbonApp::RibbonApp(int &argc, char **argv) :
    QApplication(argc, argv)
{        
    if(argc >= 2)
        settings = new Settings(QString(argv[1]), this);
    else
        settings = new Settings(this);

    cli = new FiresWSClient(this);
    notificator = new Notificator(this);
    ribbon_wnd = new RibbonWnd(RIBBON_DEPTH);
    ribbon_data = new RibbonModel(RIBBON_DEPTH, ribbon_wnd->getRibbonFontMetrics(), this);
    ribbon_wnd->setModel(ribbon_data);
    log_writer = new LogWriter(this);    

    connect(notificator, &Notificator::exitting, this, &QApplication::quit);
    connect(notificator, &Notificator::toggleRibbon, ribbon_wnd, &RibbonWnd::toggle);
    connect(notificator, &Notificator::show_settings, this, &RibbonApp::show_settings);
    connect(cli, &FiresWSClient::clientConnected, notificator, &Notificator::clientConnected);
    connect(cli, &FiresWSClient::clientDisconnected, notificator, &Notificator::clientDisconnected);

    connect(cli, &FiresWSClient::gotMessage, notificator, &Notificator::on_fires_message);
    connect(cli, &FiresWSClient::gotMessage, ribbon_data, &RibbonModel::on_fire);
    connect(cli, &FiresWSClient::gotMessage, log_writer, &LogWriter::on_fires_message);
    connect(cli, &FiresWSClient::clientConnected, this, &RibbonApp::clientConnected);
    connect(cli, &FiresWSClient::clientDisconnected, this, &RibbonApp::clientDisconnected);

    connect(settings, &Settings::changed, cli, &FiresWSClient::settings_changed);
    connect(settings, &Settings::changed, log_writer, &LogWriter::settings_changed);
    connect(settings, &Settings::changed, notificator, &Notificator::settings_changed);
    connect(settings, &Settings::changed, ribbon_data, &RibbonModel::settings_changed);

    if(!settings->load())
    {
        settings->set(
                    "",
                    "",
                    "930nyse.com",
                    8888,
                    false,
                    true,
                    true,
                    "C:/Users/Public/Documents/feed.log",
                    "Europe/Moscow");
        show_settings();
    }
}

void RibbonApp::start()
{
    setApplicationDisplayName(tr("RZ Ribbon"));
    setApplicationName(tr("RZ Ribbon"));
    setWindowIcon(QIcon(":/images/trayicon_disconnected.ico"));
    setQuitOnLastWindowClosed(false);
    notificator->show();
}

void RibbonApp::show_settings()
{
    SettingsWindow wnd(settings);
    wnd.exec();
    if(wnd.result() == QDialog::Accepted)
        wnd.updateSettings(settings);
}

void RibbonApp::clientConnected()
{
    setWindowIcon(QIcon(":/images/trayicon_connected.ico"));
}

void RibbonApp::clientDisconnected()
{
    setWindowIcon(QIcon(":/images/trayicon_disconnected.ico"));
}
