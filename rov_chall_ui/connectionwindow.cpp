#include "connectionwindow.h"
#include "ui_connectionwindow.h"
#include "libs/rosservice.h"
#include "mainwindow.h"
#include <QMessageBox>

ConnectionWindow::ConnectionWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow),
    m_argc(argc), m_argv(argv)
{
    ui->setupUi(this);
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

bool ConnectionWindow::tryToConnect() {
    if (ui->chkDefaultSettings->isChecked()) {
        return RosService::init(m_argc, m_argv, "ROV_CTRL");
    } else {
        auto masterUrl = ui->txtMasterUrl->toPlainText();
        auto hostIP = ui->txtHostIP->toPlainText();
        return RosService::init(masterUrl.toStdString(), hostIP.toStdString(), "ROV_CTRL");
    }
}

void ConnectionWindow::on_btnConnect_clicked()
{
    try {
        if (tryToConnect()) {
            MainWindow* w = new MainWindow;
            w->show();
            close();
        } else {
            QMessageBox box;
            box.setText("Error Occurred");
            box.exec();
        }
    } catch(ros::Exception e) {
        QMessageBox box;
        box.setText("Error Occurred");
        box.exec();
    }
}
