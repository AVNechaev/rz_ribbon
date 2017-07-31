#include "fireswsclient.h"

FiresWSClient::FiresWSClient(
        const QString &ip_address_,
        int port_,
        const QString &user_name_,
        const QString &pass_,
        QObject *parent) :
    QObject(parent),
    ip_address(ip_address_),
    port(port_),
    user_name(user_name_),
    pass(pass_)
{
    connect(&channel,  &QWebSocket::connected, this, &FiresWSClient::onChannelConnected);
    channel.open(QUrl("ws://930nyse.com:8888"));
}

void FiresWSClient::onChannelConnected()
{
    connect(&channel, &QWebSocket::textMessageReceived, this, &FiresWSClient::onGotFire);
    channel.sendTextMessage("{\"action\":\"auth\",\"login\":\"nechaev.andrey@gmail.com\",\"password\":\"123456\"}");
    qInfo() << "connected";
}

void FiresWSClient::onGotFire(QString data)
{
    qInfo() << "Got Message:" << data;
}
