#ifndef FIRESWSCLIENT_H
#define FIRESWSCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class FiresWSClient : public QObject
{
    Q_OBJECT

public:
    enum class State {
        CONNECTING = 1,
        CONNECTED
    };

    FiresWSClient(
            const QString& ip_address_,
            int port_,
            const QString& user_name_,
            const QString& pass_,
            QObject* parent = Q_NULLPTR);

signals:
    void clientStatusChanged(State new_state);

private slots:
    void onChannelConnected();
    void onChannelDisconnected();
    void onGotFire(QString data);

private:
    QString ip_address;
    int port;
    QString user_name;
    QString pass;

    QWebSocket channel;

    void open_channel();
};

#endif // FIRESWSCLIENT_H
