#include "notificator.h"
#include <QMenu>
#include <QDebug>
#include "settingswindow.h"

Notificator::Notificator(QObject *parent) :
    QSystemTrayIcon(parent),
    ribbon_shown(false)
{
    QIcon icon(":/images/trayicon.png");
    setIcon(icon);

    actSettings = new QAction(tr("Settings"), this);
    actToggleRibbon = new QAction(tr("Show ribbon"), this);
    actExit = new QAction(tr("Exit"), this);

    menu = new QMenu();
    menu->addAction(actSettings);
    menu->addAction(actToggleRibbon);
    menu->addSeparator();
    menu->addAction(actExit);
    setContextMenu(menu);

    connect(actSettings, &QAction::triggered, this, &Notificator::showSettings);
    connect(actToggleRibbon, &QAction::triggered, this, &Notificator::on_toggle_ribbon);
    connect(actExit, &QAction::triggered, this, &Notificator::exit);    
    setVisible(true);    
}

void Notificator::on_fires_message(FireData message)
{
    showMessage(tr("Pattern fired"), message.pattern_name + " " + message.instr_name);
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
