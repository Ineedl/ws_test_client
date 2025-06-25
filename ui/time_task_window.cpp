//
// Created by chenjiahui on 2025/6/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_time_task_window.h" resolved

#include "time_task_window.h"
#include "ui_time_task_window.h"


TimeTaskWindow::TimeTaskWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::TimeTaskWindow) {
    ui->setupUi(this);

    this->Init();
    this->InitBind();
}

TimeTaskWindow::~TimeTaskWindow() {
    delete ui;
}

void TimeTaskWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging_ = true;
        dragPosition_ = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void TimeTaskWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging_ &&father_dragging_&& (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - dragPosition_);
        event->accept();
    }
}

void TimeTaskWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging_ && father_dragging_) {
        dragging_ = false;
        event->accept();
    }
}

void TimeTaskWindow::FatherPress(){
    father_dragging_=true;
}
void TimeTaskWindow::FatherRelease(){
    father_dragging_=false;
}


void TimeTaskWindow::Init(){
    this->setWindowFlags(Qt::FramelessWindowHint);

    data_model_.setColumnCount(3);
    data_model_.setHeaderData(0, Qt::Horizontal, "ptr_num");
    data_model_.setHeaderData(1, Qt::Horizontal, "timer_time");
    data_model_.setHeaderData(2, Qt::Horizontal, "timer_data");

    this->ui->tableView->setModel(&data_model_);
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->ui->pushButton_add_timer->setText("add timer send");
    this->ui->pushButton_delete_timer->setText("del timer send");
    this->ui->label_time_task->setText("timer send");
}

void TimeTaskWindow::InitBind(){
    connect(&add_timer_window_,&AddTimerSendDataWindow::SignalAddTimerData,this,[this](int ms,const QString& send_data){
        QTimer *timer = new QTimer(this);
        TimerBind(timer,ms,send_data);
    });

    connect(this->ui->pushButton_add_timer,&QPushButton::clicked,this,[this](){
        add_timer_window_.DataClear();
        add_timer_window_.show();
    });

    connect(this->ui->pushButton_delete_timer,&QPushButton::clicked,this,[this](){
        QModelIndex index = ui->tableView->currentIndex();
        if (!index.isValid())
            return;
        QVariant value = ui->tableView->model()->index(index.row(), 0).data();
        qint64 i_p = value.toLongLong();
        QTimer* p = (QTimer*)i_p;
        delete p;
        ui->tableView->model()->removeRow(index.row());
        ui->tableView->scrollToBottom();
    });
}

void TimeTaskWindow::TimerBind(QTimer* timer,int timeout,const QString& data){
    send_data_map_.insert(timer,data);
    connect(timer,&QTimer::timeout,this,[this,data](){
        emit SignalDataSend(data);
    });

    int row = data_model_.rowCount();
    QStandardItem* item = new QStandardItem(QString::number((qint64)timer));
    item->setTextAlignment(Qt::AlignCenter);
    data_model_.setItem(row, 0, item);

    QStandardItem* item2 = new QStandardItem(QString::number(timeout));
    item->setTextAlignment(Qt::AlignCenter);
    data_model_.setItem(row, 1, item2);

    QStandardItem* item3 = new QStandardItem(data);
    item->setTextAlignment(Qt::AlignCenter);
    data_model_.setItem(row, 2, item3);

    // 滚动到底部
    this->ui->tableView->scrollToBottom();
    timer->start(timeout);
}
