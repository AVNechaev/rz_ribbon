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
    connect(&channel, &QWebSocket::connected, this, &FiresWSClient::onChannelConnected);
    connect(&channel, &QWebSocket::disconnected, this, &FiresWSClient::onChannelDisconnected);    
    open_channel();
}

void FiresWSClient::onChannelConnected()
{
    emit clientConnected();
    connect(&channel, &QWebSocket::textMessageReceived, this, &FiresWSClient::onGotFire);
    channel.sendTextMessage("{\"action\":\"auth\",\"login\":\"" + user_name + "\",\"password\":\"" + pass + "\"}");
    qDebug() << "connected";
}

void FiresWSClient::onChannelDisconnected()
{
    emit clientDisconnected();
    open_channel();
}

void FiresWSClient::onGotFire(QString data)
{
    qDebug() << "Got Message:" << data;
    emit gotMessage(data);
}

void FiresWSClient::open_channel()
{
    QUrl url;
    url.setScheme("ws");
    url.setHost(ip_address);
    url.setPort(port);
    channel.open(url);
}
