#include <QApplication>
#include <QPushButton>
#include "main_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow* window = new MainWindow();
    window->show();

    return QApplication::exec();
}
