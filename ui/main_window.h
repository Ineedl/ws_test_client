//
// Created by chenjiahui on 2025/6/20.
//

#ifndef WEBSOCKET_TEST_MAIN_WINDOW_H
#define WEBSOCKET_TEST_MAIN_WINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMouseEvent>
#include "ws_client_connection.h"
#include "time_task_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void Init();
    void InitBind();
private:
    Ui::MainWindow *ui;
    WsClientConnection ws_client_;
    QStandardItemModel data_model_;
    TimeTaskWindow time_task_window_;
    bool dragging_;
    QPoint dragPosition_;
};


#endif //WEBSOCKET_TEST_MAIN_WINDOW_H
