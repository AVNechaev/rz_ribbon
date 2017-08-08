#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

#include <QSystemTrayIcon>
#include <QMenu>
#include "firedata.h"

class Notificator : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Notificator(QObject* parent = Q_NULLPTR);

signals:
    void exitting();
    void toggleRibbon();

public slots:
    void on_fires_message(FireData message);

private slots:
    void showSettings();   
    void exit();
    void on_toggle_ribbon();

private:
    QAction* actSettings;
    QAction* actToggleRibbon;
    QAction* actExit;
    QMenu* menu;
    bool ribbon_shown;
};

#endif // NOTIFICATOR_H
