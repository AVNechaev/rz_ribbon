#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

struct Settings {
    QString login;
    QString passwd;
    QString server;
    int port;
    bool show_notifications;
    bool show_ribbon;
};

#endif // SETTINGS_H
