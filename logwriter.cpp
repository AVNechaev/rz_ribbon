#include "logwriter.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

const char IQFEED_SFX[] = ".FXCM";
const int MAX_LINES_WRITTEN = 200;

LogWriter::LogWriter(QObject *parent) :
    QObject(parent),
    tz(0),
    enabled(false),
    logname(),
    lines_written(0),
    file()
{
    tf2minutes["5MIN"] = 5;
    tf2minutes["15MIN"] = 15;
    tf2minutes["30MIN"] = 30;
    tf2minutes["HOURLY"] = 60;
    tf2minutes["4HOURS"] = 240;
}

void LogWriter::settings_changed(const Settings* settings)
{
    if((enabled == settings->isWrite_log()) && (logname == settings->getLogfile()))
        return;
    if(file.isOpen()) file.close();
    if(settings->isWrite_log())
    {        
        file.setFileName(settings->getLogfile());
        file.open(QIODevice::ReadWrite | QIODevice::Truncate);
        file.setTextModeEnabled(true);
    }
    enabled = settings->isWrite_log();
    logname = settings->getLogfile();
}

void LogWriter::on_fires_message(FireData message)
{
    QTextStream out(&file);
    QDateTime dt = QDateTime::fromString(message.fire_time, "yyyy-MM-dd'T'HH:mm:ss.000Z");
    dt.setTimeZone(tz);
    if(message.instr_name.endsWith(IQFEED_SFX)) message.instr_name.chop(sizeof(IQFEED_SFX) - 1);

    if(lines_written > MAX_LINES_WRITTEN)
    {
        file.close();        
        file.open(QIODevice::ReadWrite | QIODevice::Truncate);
        file.setTextModeEnabled(true);
        lines_written = 0;
    }
    int frame = tf2minutes.value(message.timeframe, 0);
    out << dt.toTime_t() << ";" << message.instr_name << ";" << frame << ";" << message.pattern_name << '\n';
    out.flush();
    lines_written++;
}
