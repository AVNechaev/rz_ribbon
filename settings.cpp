#include "settings.h"

#include <QFileInfo>
#include <QSettings>
#include <QStandardPaths>

Settings::Settings(QObject *)
{

}

bool Settings::load()
{    
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QString("RZ"), QString("RZ Ribbon"));
    QFileInfo finfo(settings.fileName());
    if(!(finfo.exists() && finfo.isFile()))
        return false;

    login = settings.value("login").toString();
    passwd = settings.value("passwd").toString();
    server = settings.value("server").toString();
    port = settings.value("port").toInt();
    show_notifications = settings.value("show_notifications").toBool();
    show_ribbon = settings.value("show_ribbon").toBool();
    write_log = settings.value("write_log").toBool();
    logfile = settings.value("logfile").toString();
    emit changed(this);
    return true;
}

void Settings::set(const QString &login_,
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

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QString("RZ"), QString("RZ Ribbon"));
    settings.setValue("login", login);
    settings.setValue("passwd", passwd);
    settings.setValue("server", server);
    settings.setValue("port", port);
    settings.setValue("show_notifications", show_notifications);
    settings.setValue("show_ribbon", show_ribbon);
    settings.setValue("write_log", write_log);
    settings.setValue("logfile", logfile);
    if(fl) emit changed(this);
}

QString Settings::settingsFileName() const
{
    return QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/settings.ini";
}
