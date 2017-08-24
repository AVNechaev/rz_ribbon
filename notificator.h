#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

#include <QSystemTrayIcon>
#include <QMenu>
#include "firedata.h"

class Settings;
class Notificator : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Notificator(QObject* parent = Q_NULLPTR);

signals:
    void exitting();
    void toggleRibbon();
    void show_settings();

public slots:
    void on_fires_message(FireData message);
    void settings_changed(const Settings* settings);

private slots:      
    void exit();
    void on_toggle_ribbon();

private:
    QAction* actSettings;
    QAction* actToggleRibbon;
    QAction* actExit;
    QMenu* menu;
    bool show_notifications;
    bool ribbon_shown;
};

#endif // NOTIFICATOR_H
