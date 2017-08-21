#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

signals:
    void changed(const Settings* self);

public:
    explicit Settings(QObject* = Q_NULLPTR);

    bool load();
    void store();

    void setSettings(const QString& login_,
                     const QString& passwd_,
                     const QString& server_,
                     int port_,
                     bool show_notifications_,
                     bool show_ribbon_,
                     bool write_log_,
                     const QString& logfile_);

    QString getLogin() const { return login; }
    QString getPasswd() const { return passwd; }
    QString getServer() const { return server; }
    int getPort() const { return port; }
    bool isShow_notifications() const { return show_notifications; }
    bool isShow_ribbon() const { return show_ribbon; }
    bool isWrite_log() const { return write_log; }
    QString getLogfile() const { return logfile; }

private:
    QString login;
    QString passwd;
    QString server;
    int port;
    bool show_notifications;
    bool show_ribbon;
    bool write_log;
    QString logfile;

    QString settingsFileName() const;
};


#endif // SETTINGS_H
