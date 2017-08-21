#include "fireswsclient.h"
#include <QJsonDocument>
#include <QJsonObject>

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
    timer.setInterval(10000);
    timer.start();
    connect(&channel, &QWebSocket::connected, this, &FiresWSClient::onChannelConnected);
    connect(&channel, &QWebSocket::disconnected, this, &FiresWSClient::onChannelDisconnected);    
    //connect(&timer, &QTimer::timeout, this, &FiresWSClient::onTimer);
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

    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    try
    {
        if(doc.isNull()) throw std::runtime_error("doc is null");
        const QJsonObject& obj = doc.object();
        FireData result;
        if(!obj["pattern_name"].isString()) throw std::runtime_error("no pattern_name");
        if(!obj["instr"].isString()) throw std::runtime_error("no instr");
        if(!obj["ts"].isString()) throw std::runtime_error("no ts");
        if(!obj["pattern_id"].isDouble()) throw std::runtime_error("no pattern_id");
        result.pattern_name = obj["pattern_name"].toString();
        result.instr_name = obj["instr"].toString();
        result.fire_time = obj["ts"].toString();
        result.pattern_id = obj["pattern_id"].toInt();
        emit gotMessage(result);
    }
    catch(const std::runtime_error& e)
    {
        qWarning() << "undecoded message: " << data << ": " << e.what();
    }
}

void FiresWSClient::onTimer()
{
    static int cnt=0;
    QString data = QString("ByTimer %1").arg(cnt++);
    emit gotMessage(FireData{0, data, "-", "Now"});
}

void FiresWSClient::open_channel()
{
    QUrl url;
    url.setScheme("ws");
    url.setHost(ip_address);
    url.setPort(port);
    channel.open(url);
}
