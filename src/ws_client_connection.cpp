//
// Created by chenjiahui on 2025/6/20.
//

#include "../head/ws_client_connection.h"

void WsClientConnection::SendWsTextData(const QString& str) {
    auto state = web_socket_.state();
    if (state == QAbstractSocket::ConnectedState) {
        web_socket_.sendTextMessage(str);
    } else if (state == QAbstractSocket::ConnectingState) {
        qDebug() << "WebSocket 正在连接中";
    } else {
        qDebug() << "WebSocket 未连接，当前状态：" << state;
    }
}
void WsClientConnection::SendWsByteData(const QByteArray & str){
    auto state = web_socket_.state();
    if (state == QAbstractSocket::ConnectedState) {
        web_socket_.sendBinaryMessage(str);
    } else if (state == QAbstractSocket::ConnectingState) {
        qDebug() << "WebSocket 正在连接中";
    } else {
        qDebug() << "WebSocket 未连接，当前状态：" << state;
    }
}

WsClientConnection::WsClientConnection(){
    QObject::connect(&web_socket_, &QWebSocket::connected, [&]() {
        qDebug() << "Connected to server";
        emit Connected();
    });

    QObject::connect(&web_socket_, &QWebSocket::textMessageReceived,
     [&](const QString &message) {
         emit RecvWsData(message);
     });

    QObject::connect(&web_socket_, &QWebSocket::binaryMessageReceived,
                     [&](const QString &message) {
                         emit RecvWsData(message);
                     });

    QObject::connect(&web_socket_, &QWebSocket::disconnected, [&]() {
        emit DisConnected();
    });

    QObject::connect(&web_socket_, &QWebSocket::stateChanged,
                     [this](QAbstractSocket::SocketState state) {
                         switch (state) {
                             case QAbstractSocket::ConnectedState:
                                 qDebug() << "已连接";
                                 break;
                             case QAbstractSocket::UnconnectedState:
                                 qDebug() << "未连接";
                                 break;
                             case QAbstractSocket::ConnectingState:
                                 qDebug() << "正在连接中";
                                 break;
                             default:
                                 qDebug() << "其他状态:" << state;
                                 break;
                         }
                         emit WsStatusChange(state);
                     });
}
void WsClientConnection::SetDst(const QString& dst,const QString& crt,const QString& key,bool enable_ssl){
    this->dst_address_ = dst;
    this->crt_file_path_ = crt;
    this->key_file_path_ = key;
    this->use_ssl_ = enable_ssl;
}
void WsClientConnection::StartConnect(){
    web_socket_.open(QUrl(dst_address_));
}
void WsClientConnection::StopConnect(){
    web_socket_.close();
}