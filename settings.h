#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <memory>
#include <QTimeZone>

class Settings : public QObject
{
    Q_OBJECT

signals:
    void changed(const Settings* self);

public:
    explicit Settings(QObject* = Q_NULLPTR);
    explicit Settings(QString custom_filename, QObject* = Q_NULLPTR);

    bool load();
    void store();

    void set(const QString& login_,
             const QString& passwd_,
             const QString& server_,
             int port_,
             bool show_notifications_,
             bool show_ribbon_,
             bool write_log_,
             const QString& logfile_,
             const QByteArray& timezone_
             );

    QString getLogin() const { return login; }
    QString getPasswd() const { return passwd; }
    QString getServer() const { return server; }
    int getPort() const { return port; }
    bool isShow_notifications() const { return show_notifications; }
    bool isShow_ribbon() const { return show_ribbon; }
    bool isWrite_log() const { return write_log; }
    QString getLogfile() const { return logfile; }
    const QTimeZone& getTimezone() const { return timezone; }

    template<typename T>
    static bool set_val(T& cur_data, const T& new_data)
    {
        if(cur_data != new_data) {cur_data = new_data; return true; }
        return false;
    }

private:
    bool use_custom_file;
    QString custom_filename;

    QString login;
    QString passwd;
    QString server;
    int port;
    bool show_notifications;
    bool show_ribbon;
    bool write_log;
    QString logfile;
    QTimeZone timezone;

    std::unique_ptr<QSettings> init_settings_file();
};


#endif // SETTINGS_H
