#include "notificator.h"
#include <QMenu>
#include <QDebug>
#include "settingswindow.h"
#include "settings.h"

Notificator::Notificator(QObject *parent) :
    QSystemTrayIcon(parent),
    show_notifications(false),
    ribbon_shown(false),
    icon_connected(":/images/trayicon_connected.ico"),
    icon_disconnected(":/images/trayicon_disconnected.ico")
{
    setIcon(icon_disconnected);

    actSettings = new QAction(tr("Settings"), this);
    actToggleRibbon = new QAction(tr("Show ribbon"), this);
    actExit = new QAction(tr("Exit"), this);

    menu = new QMenu();
    menu->addAction(actSettings);
    menu->addAction(actToggleRibbon);
    menu->addSeparator();
    menu->addAction(actExit);
    setContextMenu(menu);

    connect(actSettings, &QAction::triggered, this, &Notificator::show_settings);
    connect(actToggleRibbon, &QAction::triggered, this, &Notificator::on_toggle_ribbon);
    connect(actExit, &QAction::triggered, this, &Notificator::exit);    
    setVisible(true);    
}

void Notificator::on_fires_message(FireData message)
{
    if(show_notifications)
        showMessage(tr("Pattern fired"), message.pattern_name + " " + message.instr_name);
}

void Notificator::settings_changed(const Settings *settings)
{
    show_notifications = settings->isShow_notifications();
    if(settings->isShow_ribbon())
        actToggleRibbon->setEnabled(true);
    else
    {
        actToggleRibbon->setEnabled(false);
        if(ribbon_shown) on_toggle_ribbon();
    }
}

void Notificator::clientConnected()
{    
    setIcon(icon_connected);
}

void Notificator::clientDisconnected()
{
    setIcon(icon_disconnected);
}

void Notificator::exit()
{
    hide();
    emit exitting();
}

void Notificator::on_toggle_ribbon()
{
    if(ribbon_shown)
    {
        ribbon_shown = false;
        actToggleRibbon->setText(tr("Show ribbon"));
    }
    else
    {
        ribbon_shown = true;
        actToggleRibbon->setText(tr("Hide ribbon"));
    }
    emit toggleRibbon();
}
