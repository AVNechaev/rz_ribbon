#include "settings.h"

#include <QSettings>
#include <QStandardPaths>

template<typename T>
bool set_val(T& cur_data, const T& new_data)
{
    if(cur_data != new_data) {cur_data = new_data; return true; }
    return false;
}

Settings::Settings(QObject *)
{

}

bool Settings::load()
{
    return false;
    QSettings settings(settingsFileName(), QSettings::IniFormat);

//    QString server_ip = settings.value("server_ip", "91.102.155.28").toString();
//    quint16 server_port = (quint16)settings.value("server_port", "10123").toInt();
//    QString images_server_prefix = settings.value("images_server_prefix", "http://91.102.155.28/is/?link=").toString();
}

void Settings::setSettings(const QString &login_,
        const QString &passwd_,
        const QString &server_,
        int port_,
        bool show_notifications_,
        bool show_ribbon_,
        bool write_log_,
        const QString &logfile_)
{
    bool fl = false;
    fl |= set_val(login, login_);
    fl |= set_val(passwd, passwd_);
    fl |= set_val(server, server_);
    fl |= set_val(port, port_);
    fl |= set_val(show_notifications, show_notifications_);
    fl |= set_val(show_ribbon, show_ribbon_);
    fl |= set_val(write_log, write_log_);
    fl |= set_val(logfile, logfile_);
    if(fl) emit changed(this);
}

QString Settings::settingsFileName() const
{
    return QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/settings.ini";
}
