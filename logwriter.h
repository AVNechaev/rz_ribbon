#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <QObject>
#include <QFile>
#include <QTimeZone>
#include "firedata.h"
#include "settings.h"

class Settings;

class LogWriter : public QObject
{
    Q_OBJECT

public:
    LogWriter(QObject *parent = Q_NULLPTR);

public slots:
    void settings_changed(const Settings* settings);
    void on_fires_message(FireData message);

private:
    const QTimeZone tz;
    bool enabled;
    QString logname;
    int lines_written;
    QFile file;

    QMap<QString, int> tf2minutes;
};

#endif // LOGWRITER_H
