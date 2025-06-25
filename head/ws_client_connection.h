//
// Created by chenjiahui on 2025/6/20.
//

#ifndef WEBSOCKET_TEST_WSCONNECTION_H
#define WEBSOCKET_TEST_WSCONNECTION_H

#include <QtWebSockets/QWebSocket>
#include <QObject>
#include <mutex>

class WsClientConnection:public QObject {

Q_OBJECT

signals:
    void RecvWsData(const QString& str);
    void Connected();
    void DisConnected();
    void WsStatusChange(const QAbstractSocket::SocketState& now_state);

public slots:
    void SendWsTextData(const QString& str);
    void SendWsByteData(const QByteArray& str);

public:
    explicit WsClientConnection();
    void SetDst(const QString& dst,const QString& crt,const QString& key,bool enable_ssl);
    void StartConnect();
    void StopConnect();

private:
    QWebSocket web_socket_;
    QString dst_address_;
    QString crt_file_path_;
    QString key_file_path_;
    bool use_ssl_;
    std::mutex write_mutex_;
};


#endif //WEBSOCKET_TEST_WSCONNECTION_H
