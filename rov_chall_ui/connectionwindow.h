#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectionWindow(int argc, char** argv, QWidget *parent = nullptr);
    ~ConnectionWindow();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::ConnectionWindow *ui;
    int m_argc;
    char** m_argv;

    bool tryToConnect();
};

#endif // CONNECTIONWINDOW_H
