#include "logwriter.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

const char IQFEED_SFX[] = ".FXCM";
const int MAX_LINES_WRITTEN = 200;

LogWriter::LogWriter(QObject *parent) :
    QObject(parent),
    tz(0),
    lines_written(0),
    file(),
    enabled(false)
{

}

void LogWriter::settings_changed(const Settings* settings)
{
//    TODO: filename change is not handled; should reset the log flag too;
    if(enabled == settings->isWrite_log()) return;
    if(file.isOpen()) file.close();
    if(settings->isWrite_log())
    {
        file.setFileName(settings->getLogfile());
        file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    }
    enabled = settings->isWrite_log();
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
        lines_written = 0;
    }
    out << dt.toTime_t() << ";" << message.instr_name << ";" << '\n';
    out.flush();
    lines_written++;
}
