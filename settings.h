#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

struct Settings : public QObject
{
    Q_OBJECT

signals:
    void changed(const Settings& self);

public:
    explicit Settings(QObject* = Q_NULLPTR) {}

    QString getLogin() const;
    void setLogin(const QString &value);

    QString getPasswd() const;
    void setPasswd(const QString &value);

    QString getServer() const;
    void setServer(const QString &value);

    int getPort() const;
    void setPort(int value);

    bool isShow_notifications() const;
    void setShow_notifications(bool value);

    bool isShow_ribbon() const;
    void setShow_ribbon(bool value);

    QString getLogfile() const;
    void setLogfile(const QString &value);

private:
    QString login;
    QString passwd;
    QString server;
    int port;
    bool show_notifications;
    bool show_ribbon;

    QString logfile;
};


#endif // SETTINGS_H
