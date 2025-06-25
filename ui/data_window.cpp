//
// Created by chenjiahui on 2025/6/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_data_window.h" resolved

#include "data_window.h"
#include "ui_data_window.h"


DataWindow::DataWindow(const QString& show_data,QWidget *parent) :
        QWidget(parent), ui(new Ui::DataWindow) {
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText(show_data);
}

DataWindow::~DataWindow() {
    delete ui;
    qDebug()<<"data window destroy";
}
