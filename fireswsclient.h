#ifndef FIRESWSCLIENT_H
#define FIRESWSCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include "firedata.h"
#include <QTimer>

class Settings;
class FiresWSClient : public QObject
{
    Q_OBJECT

public:
    FiresWSClient(
            const QString& ip_address_,
            int port_,
            const QString& user_name_,
            const QString& pass_,
            QObject* parent = Q_NULLPTR);

    FiresWSClient(QObject* parent = Q_NULLPTR);

signals:
    void clientConnected();
    void clientDisconnected();
    void gotMessage(FireData data);

public slots:
    void settings_changed(const Settings *settings);

private slots:
    void onChannelConnected();
    void onChannelDisconnected();
    void onGotFire(QString data);
    void onTimer();    
    void onSslErrors(const QList<QSslError> &errors);
    void open_channel();

private:
    QString ip_address;
    int port;
    QString user_name;
    QString pass;

    QWebSocket channel;

    QTimer timer, reconnect_timer;
    qint64 last_ping;    
};

#endif // FIRESWSCLIENT_H
