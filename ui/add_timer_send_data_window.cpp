//
// Created by chenjiahui on 2025/6/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_add_timer_send_data_window.h" resolved

#include "add_timer_send_data_window.h"
#include "ui_add_timer_send_data_window.h"


AddTimerSendDataWindow::AddTimerSendDataWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::AddTimerSendDataWindow) {
    ui->setupUi(this);
    this->Init();
    this->InitBind();
}

AddTimerSendDataWindow::~AddTimerSendDataWindow() {
    delete ui;
}

void AddTimerSendDataWindow::DataClear(){
    this->ui->plainTextEdit_data->clear();
    this->ui->lineEdit_num->clear();
}

void AddTimerSendDataWindow::Init(){
    this->ui->label_unit->setText("ms");
    this->ui->pushButton_add->setText("add timer");

    this->setWindowModality(Qt::ApplicationModal);
}

void AddTimerSendDataWindow::InitBind() {
    connect(this->ui->pushButton_add,&QPushButton::clicked,this,[this](){
        QString ms = this->ui->lineEdit_num->text();
        int i_ms = ms.toInt();
        QString send_data = this->ui->plainTextEdit_data->toPlainText();
        if(i_ms==0 || send_data.isEmpty()){
            return;
        }
        emit SignalAddTimerData(i_ms,send_data);
        this->close();
    });
}