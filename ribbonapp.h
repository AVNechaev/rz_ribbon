#ifndef RIBBONAPP_H
#define RIBBONAPP_H

#include <QApplication>

class FiresWSClient;
class Notificator;

class RibbonApp : public QApplication
{
    Q_OBJECT
public:
    RibbonApp(int argc, char** argv);

    void start();

private:
    FiresWSClient* cli;
    Notificator* notificator;
};

#endif // RIBBONAPP_H
