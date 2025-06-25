//
// Created by chenjiahui on 2025/6/25.
//

#ifndef WEBSOCKET_TEST_ADD_TIMER_SEND_DATA_WINDOW_H
#define WEBSOCKET_TEST_ADD_TIMER_SEND_DATA_WINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class AddTimerSendDataWindow; }
QT_END_NAMESPACE

class AddTimerSendDataWindow : public QWidget {
Q_OBJECT
signals:
    void SignalAddTimerData(int ms,const QString& sendData);

public:
    explicit AddTimerSendDataWindow(QWidget *parent = nullptr);

    ~AddTimerSendDataWindow() override;
    void DataClear();
private:
    void Init();
    void InitBind();
private:
    Ui::AddTimerSendDataWindow *ui;
};


#endif //WEBSOCKET_TEST_ADD_TIMER_SEND_DATA_WINDOW_H
