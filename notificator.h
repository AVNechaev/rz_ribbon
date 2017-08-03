#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

#include <QSystemTrayIcon>
#include "fireswsclient.h"

class Notificator : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Notificator(QObject* parent = Q_NULLPTR);

public slots:
    void on_fires_message(QString message);

};

#endif // NOTIFICATOR_H
