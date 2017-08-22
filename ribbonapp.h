#ifndef RIBBONAPP_H
#define RIBBONAPP_H

#include <QApplication>

class FiresWSClient;
class Notificator;
class RibbonWnd;
class RibbonModel;
class LogWriter;
class Settings;

class RibbonApp : public QApplication
{
    Q_OBJECT
public:
    RibbonApp(int &argc, char** argv);
    void start();

private:
    FiresWSClient* cli;
    Notificator* notificator;
    RibbonWnd* ribbon_wnd;
    RibbonModel* ribbon_data;
    LogWriter* log_writer;
    Settings* settings;

    static const size_t RIBBON_DEPTH = 10;
};

#endif // RIBBONAPP_H
