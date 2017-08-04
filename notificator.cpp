#include "notificator.h"
#include <QMenu>
#include "settingswindow.h"

Notificator::Notificator(QObject *parent) :
    QSystemTrayIcon(parent)
{
    QIcon icon(":/images/trayicon.png");
    setIcon(icon);

    actSettings = new QAction(tr("Settings"), this);
    actExit = new QAction(tr("Exit"), this);

    menu = new QMenu();
    menu->addAction(actSettings);
    menu->addSeparator();
    menu->addAction(actExit);
    setContextMenu(menu);

    connect(actSettings, &QAction::triggered, this, &Notificator::showSettings);
    connect(actExit, &QAction::triggered, this, &Notificator::exit);
    setVisible(true);
}

void Notificator::on_fires_message(QString message)
{
    showMessage("new message", message);
}

void Notificator::showSettings()
{
    SettingsWindow wnd;
    wnd.exec();
}

void Notificator::exit()
{
    hide();
    emit exitting();
}
