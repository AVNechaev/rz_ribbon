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
    emit clientStatusChanged(State::CONNECTING);
    open_channel();
}

void FiresWSClient::onChannelConnected()
{
    emit clientStatusChanged(State::CONNECTED);
    connect(&channel, &QWebSocket::textMessageReceived, this, &FiresWSClient::onGotFire);
    channel.sendTextMessage("{\"action\":\"auth\",\"login\":\"nechaev.andrey@gmail.com\",\"password\":\"123456\"}");
    qInfo() << "connected";
    emit gotMessage("connected");
}

void FiresWSClient::onChannelDisconnected()
{
    emit clientStatusChanged(State::CONNECTING);
    open_channel();
}

void FiresWSClient::onGotFire(QString data)
{
    qInfo() << "Got Message:" << data;
    emit gotMessage(data);
}

void FiresWSClient::open_channel()
{
    QUrl url;
    url.setScheme("ws");
    url.setHost("930nyse.com");
    url.setPort(port);
    channel.open(url);
}
