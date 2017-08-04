#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

#include <QSystemTrayIcon>
#include <QMenu>

class Notificator : public QSystemTrayIcon
{
    Q_OBJECT

public:
    Notificator(QObject* parent = Q_NULLPTR);

signals:
    void exitting();

public slots:
    void on_fires_message(QString message);

private slots:
    void showSettings();
    void exit();

private:
    QAction* actSettings;
    QAction* actExit;
    QMenu* menu;
};

#endif // NOTIFICATOR_H
