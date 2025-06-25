//
// Created by chenjiahui on 2025/6/24.
//

#ifndef WEBSOCKET_TEST_TIME_TASK_WINDOW_H
#define WEBSOCKET_TEST_TIME_TASK_WINDOW_H

#include <QWidget>
#include <QTimer>
#include <QMap>
#include <QStandardItemModel>
#include <QMouseEvent>
#include "add_timer_send_data_window.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TimeTaskWindow; }
QT_END_NAMESPACE

class TimeTaskWindow : public QWidget {
Q_OBJECT

signals:
    void SignalDataSend(const QString& data);

public:
    explicit TimeTaskWindow(QWidget *parent = nullptr);

    ~TimeTaskWindow() override;

public:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void FatherPress();
    void FatherRelease();

private:
    void Init();
    void InitBind();
    void TimerBind(QTimer* timer,int timeout,const QString& data);
private:
    Ui::TimeTaskWindow *ui;
    QMap<QTimer*,QString> send_data_map_;
    QStandardItemModel data_model_;
    bool dragging_;
    bool father_dragging_;
    QPoint dragPosition_;

    AddTimerSendDataWindow add_timer_window_;
};


#endif //WEBSOCKET_TEST_TIME_TASK_WINDOW_H
