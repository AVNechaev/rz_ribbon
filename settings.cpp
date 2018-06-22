#include "settings.h"

#include <QFileInfo>
#include <QStandardPaths>

Settings::Settings(QObject * parent) :
    QObject(parent),
    use_custom_file(false)
{
}

Settings::Settings(QString custom_filename_, QObject * parent) :
    QObject(parent),
    use_custom_file(true),
    custom_filename(custom_filename_)
{
}

bool Settings::load()
{    
    std::unique_ptr<QSettings> settings = init_settings_file();
    QFileInfo finfo(settings->fileName());
    if(!(finfo.exists() && finfo.isFile()))
        return false;

    login = settings->value("login").toString();
    passwd = settings->value("passwd").toString();
    server = settings->value("server").toString();
    port = settings->value("port").toInt();
    show_notifications = settings->value("show_notifications").toBool();
    show_ribbon = settings->value("show_ribbon").toBool();
    write_log = settings->value("write_log").toBool();
    logfile = settings->value("logfile").toString();
    timezone = QTimeZone(settings->value("timezone").toByteArray());

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
                   const QString &logfile_,
                   const QByteArray& timezone_)
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
    if(timezone.id() != timezone_)
    {
        timezone = QTimeZone(timezone_);
        fl = true;
    }

    std::unique_ptr<QSettings> settings = init_settings_file();
    settings->setValue("login", login);
    settings->setValue("passwd", passwd);
    settings->setValue("server", server);
    settings->setValue("port", port);
    settings->setValue("show_notifications", show_notifications);
    settings->setValue("show_ribbon", show_ribbon);
    settings->setValue("write_log", write_log);
    settings->setValue("logfile", logfile);
    settings->setValue("timezone", timezone.id());
    if(fl) emit changed(this);
}

std::unique_ptr<QSettings> Settings::init_settings_file()
{
    if(use_custom_file)
        return std::unique_ptr<QSettings>(new QSettings(custom_filename, QSettings::IniFormat));
    else
        return std::unique_ptr<QSettings>(new QSettings(QSettings::IniFormat, QSettings::UserScope, QString("RZ"), QString("RZ Ribbon")));
}
