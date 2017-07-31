#ifndef FIRESWSCLIENT_H
#define FIRESWSCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class FiresWSClient : public QObject
{
public:
    FiresWSClient(
            const QString& ip_address_,
            int port_,
            const QString& user_name_,
            const QString& pass_,
            QObject* parent = Q_NULLPTR);

private slots:
    void onChannelConnected();
    void onGotFire(QString data);

private:
    QString ip_address;
    int port;
    QString user_name;
    QString pass;

    QWebSocket channel;
};

#endif // FIRESWSCLIENT_H
