//
// Created by chenjiahui on 2025/6/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include "main_window.h"
#include "ui_main_window.h"
#include "data_window.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->Init();
    this->InitBind();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    time_task_window_.FatherPress();
    if (event->button() == Qt::LeftButton) {
        dragging_ = true;
        dragPosition_ = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    time_task_window_.mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging_ && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - dragPosition_);
        event->accept();
    }
    time_task_window_.mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging_) {
        dragging_ = false;
        event->accept();
    }
    time_task_window_.mouseReleaseEvent(event);
    time_task_window_.FatherRelease();
}


void MainWindow::Init(){
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->ui->comboBox_protocol->addItem("ws://");
    this->ui->comboBox_protocol->addItem("wss://");
    this->ui->label_send->setText("send msg");
    this->ui->pushButton_send->setText("send");
    this->ui->pushButton_connect->setText("connect");

    this->ui->comboBox_protocol->setCurrentIndex(0);
    this->ui->label_state->setText("disconnect");

    this->ui->pushButton_timer_set->setText("time task");

    data_model_.setColumnCount(1);
    data_model_.setHeaderData(0, Qt::Horizontal, "recv data");

    this->ui->tableView->setModel(&data_model_);
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->ui->pushButton_min->setText("-");
    this->ui->pushButton_close->setText("X");
    this->ui->label_title->setText("websocket client test");
}

void MainWindow::InitBind(){

    connect(this->ui->tableView, &QTableView::doubleClicked,
            [this](const QModelIndex &index) {
                DataWindow* window = new DataWindow(this->data_model_.data(index).toString());
                window->setAttribute(Qt::WA_DeleteOnClose);
                window->show();
            });

    connect(&this->ws_client_,&WsClientConnection::WsStatusChange,this,[this](const QAbstractSocket::SocketState& now_state){
        switch (now_state) {
            case QAbstractSocket::ConnectedState:
                this->ui->label_state->setText("connected");
                break;
            case QAbstractSocket::UnconnectedState:
                this->ui->label_state->setText("disconnect");
                break;
            case QAbstractSocket::ConnectingState:
                this->ui->label_state->setText("connecting");
                break;
            default:
                this->ui->label_state->setText("other");
                break;
        }
    });

    connect(&this->ws_client_,&WsClientConnection::RecvWsData,this,[this](const QString& data){
        int row = data_model_.rowCount();
        QStandardItem* item = new QStandardItem(data);
        item->setTextAlignment(Qt::AlignCenter);
        data_model_.setItem(row, 0, item);

        // 滚动到底部
        this->ui->tableView->scrollToBottom();
    });

    connect(ui->pushButton_send,&QPushButton::clicked,this,[this](){
        QString send_data = this->ui->plainTextEdit->toPlainText();
        ws_client_.SendWsTextData(send_data);
    });

    connect(ui->pushButton_connect,&QPushButton::clicked,this,[this](){
        QString address = this->ui->lineEdit_address->text();
        address = this->ui->comboBox_protocol->currentText()+address;
        ws_client_.SetDst(address,"","",false);
        ws_client_.StartConnect();
    });


    connect(ui->pushButton_timer_set,&QPushButton::clicked,this,[this](){
        if(!time_task_window_.isVisible()){
            // 获取主窗口左上角的屏幕坐标
            QPoint mainPos = this->pos();  // 或 this->frameGeometry().topLeft()

            // 获取弹出窗口自身的尺寸
            QSize popupSize = time_task_window_.size();

            // 设置弹出窗口位置：在主窗口左边，与主窗口垂直对齐
            int x = mainPos.x() - popupSize.width();
            int y = mainPos.y();  // 顶部对齐，如要垂直居中可改成：mainPos.y() + (this->height() - popupSize.height()) / 2

            time_task_window_.move(x, y);
            time_task_window_.show();
        }else{
            time_task_window_.close();
        }

    });

    connect(this,&QWidget::close,this,[this](){
       time_task_window_.close();
    });

    connect(&this->time_task_window_,&TimeTaskWindow::SignalDataSend,this,[this](const QString& send_data){
        ws_client_.SendWsTextData(send_data);
    });

    connect(this->ui->pushButton_close,&QPushButton::clicked,this,[this](){
        this->close();
    });
    connect(this->ui->pushButton_min,&QPushButton::clicked,this,[this](){
        this->showMinimized();
    });
}
