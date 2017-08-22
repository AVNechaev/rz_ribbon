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
    pat_id2tf = std::map<int, int> {
        {2235, 5},
        {2237, 15},
        {2238, 30},
        {2239, 60},
        {2240, 240},
        {2241, 5},
        {2242, 15},
        {2243, 30},
        {2244, 60},
        {2245, 240},
        {2246, 5},
        {2247, 15},
        {2248, 30},
        {2249, 60},
        {2250, 240},
        {2251, 5},
        {2252, 15},
        {2253, 30},
        {2254, 60},
        {2255, 240},
        {2256, 5},
        {2257, 15},
        {2258, 30},
        {2259, 60},
        {2260, 240},
        {2261, 5},
        {2262, 15},
        {2263, 30},
        {2264, 60},
        {2265, 240},
        {2266, 5},
        {2267, 15},
        {2268, 30},
        {2269, 60},
        {2270, 240},
        {2271, 5},
        {2272, 15},
        {2273, 30},
        {2274, 60},
        {2275, 240},
        {2276, 5},
        {2277, 15},
        {2278, 30},
        {2279, 60},
        {2280, 240},
        {2281, 5},
        {2282, 15},
        {2283, 30},
        {2284, 60},
        {2285, 240},
        {2307, 5},
        {2308, 5},
        {2309, 5},
        {2310, 5},
        {2311, 5},
        {2312, 5},
        {2313, 5},
        {2314, 5},
        {2315, 5},
        {2316, 5},
        {2317, 5},
        {2318, 5},
        {2319, 5},
        {2320, 5},
        {2321, 5},
        {2322, 5},
        {2323, 5},
        {2324, 5},
        {2325, 5},
        {2326, 5},
        {2328, 5}
    };
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
        file.setTextModeEnabled(true);
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
        file.setTextModeEnabled(true);
        lines_written = 0;
    }
    int frame = 0;
    auto it = pat_id2tf.find(message.pattern_id);
    if(it != pat_id2tf.end())
        frame = it->second;
    out << dt.toTime_t() << ";" << message.instr_name << ";" << frame << '\n';
    out.flush();
    lines_written++;
}
