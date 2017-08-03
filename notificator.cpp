#include "notificator.h"
#include <QMenu>

Notificator::Notificator(QObject *parent) :
    QSystemTrayIcon(parent)
{
    QIcon icon("qrc:///images/trayicon.ico");
    qInfo() << icon.isNull();
    setIcon(icon);
    setVisible(true);
}

void Notificator::on_fires_message(QString message)
{
    showMessage("new message", message);
}
