#include "keybindings.h"
#include "ui_keybindings.h"

keyBindings::keyBindings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::keyBindings)
{
    ui->setupUi(this);
}

keyBindings::~keyBindings()
{
    delete ui;
}
