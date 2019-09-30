#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include <QDialog>
#include <QDebug>

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

private:
    Ui::keyBindings *ui;
};

#endif // KEYBINDINGS_H
