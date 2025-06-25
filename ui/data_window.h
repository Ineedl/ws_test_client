//
// Created by chenjiahui on 2025/6/20.
//

#ifndef WEBSOCKET_TEST_DATA_WINDOW_H
#define WEBSOCKET_TEST_DATA_WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DataWindow; }
QT_END_NAMESPACE

class DataWindow : public QWidget {
Q_OBJECT

public:
    explicit DataWindow(const QString& show_data,QWidget *parent = nullptr);

    ~DataWindow() override;

private:
    Ui::DataWindow *ui;
};


#endif //WEBSOCKET_TEST_DATA_WINDOW_H
