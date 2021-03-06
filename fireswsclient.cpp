//temrorary hack to allow glog.lib be linked as static
//disable __declspec(dllimport)
#define GOOGLE_GLOG_DLL_DECL

#include "fireswsclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include "settings.h"
#include "glog/logging.h"

const qint64 PING_MISS_TIMEOUT = 3 * 60 * 1000;
const qint64 RECONNECT_TIMEOUT = 1000;
FiresWSClient::FiresWSClient(
        const QString &ip_address_,
        int port_,
        const QString &user_name_,
        const QString &pass_,
        QObject *parent) :
    FiresWSClient(parent)
{
    ip_address = ip_address_;
    port = port_;
    user_name = user_name_;
    pass = pass_;
    open_channel();
}

FiresWSClient::FiresWSClient(QObject *parent) :
    QObject(parent),
    ip_address(),
    port(0),
    user_name(),
    pass()
{
    timer.setInterval(PING_MISS_TIMEOUT);
    reconnect_timer.setInterval(RECONNECT_TIMEOUT);

    connect(&timer, &QTimer::timeout, this, &FiresWSClient::onTimer);

    typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);
    connect(&channel, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors), this, &FiresWSClient::onSslErrors);
    connect(&channel, &QWebSocket::connected, this, &FiresWSClient::onChannelConnected);
    connect(&channel, &QWebSocket::disconnected, this, &FiresWSClient::onChannelDisconnected);
    connect(&channel, &QWebSocket::textMessageReceived, this, &FiresWSClient::onGotFire);
    connect(&reconnect_timer, &QTimer::timeout, this, &FiresWSClient::open_channel);
}

void FiresWSClient::onChannelConnected()
{
    LOG(INFO) << "Client connected";
    emit clientConnected();
    channel.sendTextMessage("{\"action\":\"auth\",\"login\":\"" + user_name + "\",\"password\":\"" + pass + "\"}");
    qDebug() << "connected";
    last_ping = QDateTime::currentMSecsSinceEpoch();
    timer.start();
}

void FiresWSClient::onChannelDisconnected()
{
    qDebug() << "WS channel disconnected; " << channel.errorString();
    LOG(WARNING) << "WS channel disconnected; " << channel.errorString().toStdString();
    timer.stop();
    emit clientDisconnected();
    reconnect_timer.setSingleShot(true);
    reconnect_timer.start();
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
        if(!obj["type"].isString()) throw std::runtime_error("no type field");
        QString type = obj["type"].toString();
        if(type == "ping")
        {
            last_ping = QDateTime::currentMSecsSinceEpoch();
        }
        else if(type == "fire")
        {
            if(!obj["pattern_name"].isString()) throw std::runtime_error("no pattern_name");
            if(!obj["instr"].isString()) throw std::runtime_error("no instr");
            if(!obj["ts"].isString()) throw std::runtime_error("no ts");
            if(!obj["pattern_id"].isDouble()) throw std::runtime_error("no pattern_id");
            if(!obj["timeframe"].isString()) throw std::runtime_error("no timeframe");
            result.pattern_name = obj["pattern_name"].toString();
            result.instr_name = obj["instr"].toString();
            result.fire_time = obj["ts"].toString();
            result.pattern_id = obj["pattern_id"].toInt();
            result.timeframe = obj["timeframe"].toString();
            if(obj["vartext"].isString())
                result.vartext = obj["vartext"].toString();
            emit gotMessage(result);
        }
    }
    catch(const std::runtime_error& e)
    {
        LOG(WARNING) << "undecoded message: " << data.toStdString() << ": " << e.what();
    }
}

void FiresWSClient::onTimer()
{
    qDebug() << PING_MISS_TIMEOUT <<" ; " << last_ping << QDateTime::currentMSecsSinceEpoch() << QDateTime::currentDateTime();
    if((QDateTime::currentMSecsSinceEpoch() - last_ping) > PING_MISS_TIMEOUT)
    {
        LOG(WARNING) << "WS ping timeout";
        LOG(WARNING) << PING_MISS_TIMEOUT <<" ; " << last_ping << QDateTime::currentMSecsSinceEpoch() << QDateTime::currentDateTime().toString().toStdString();
        channel.close(QWebSocketProtocol::CloseCodeProtocolError, "ping timeout");
    }
}

void FiresWSClient::settings_changed(const Settings *settings)
{
    bool changed = false;
    changed |= Settings::set_val(ip_address, settings->getServer());
    changed |= Settings::set_val(port, settings->getPort());
    changed |= Settings::set_val(user_name, settings->getLogin());
    changed |= Settings::set_val(pass, settings->getPasswd());
    if(changed)
        if(channel.isValid())
        {
            LOG(INFO) << "Closing as settings changed";
            channel.close(QWebSocketProtocol::CloseCodeGoingAway, "credentials changed");
        }
        else
            open_channel();
}

void FiresWSClient::open_channel()
{
    if(user_name.isEmpty() || pass.isEmpty() || ip_address.isEmpty() || port == 0)
        return;

    QUrl url;
    //    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryVersionString();// << QSslConfiguration::supportedCiphers();
    url.setScheme("ws");
    url.setHost(ip_address);
    url.setPort(port);
    channel.open(url);
}

void FiresWSClient::onSslErrors(const QList<QSslError> &errors)
{
    for(const auto err : errors.toStdList())
        LOG(WARNING) << "WSS error: " << err.errorString().toStdString();
}
