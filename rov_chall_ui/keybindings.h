#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

namespace Ui {
class keyBindings;
}

class keyBindings : public QDialog
{
    Q_OBJECT

public:
    explicit keyBindings(QWidget *parent = nullptr);
    ~keyBindings();

private slots:
    void loadData();
    void on_close_dialogButtonBox_accepted();

    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButton10_clicked();
    void on_pushButton11_clicked();
    void on_pushButton12_clicked();

private:
    Ui::keyBindings *ui;
    QJsonDocument jsonDocument;
    QJsonObject json;

signals:
    void updatedKeyBindings();

};

#endif // KEYBINDINGS_H
