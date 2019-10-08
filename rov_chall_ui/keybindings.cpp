#include "keybindings.h"
#include "ui_keybindings.h"

keyBindings::keyBindings(QWidget *parent) : QDialog(parent), ui(new Ui::keyBindings){
    ui->setupUi(this);
    loadData();
}

keyBindings::~keyBindings()
{
    delete ui;
}

void keyBindings::loadData(){
    QString openFileName = QFileDialog::getOpenFileName(this, tr("Open Settings File"), QString(QDir::currentPath()), tr("JSON (*.json)"));
    QFileInfo fileInfo(openFileName);   // Using QFileInfo
    QDir::setCurrent(fileInfo.path());  // set the current working directory where the file will be
    // Create a file object and open it for reading.
    QFile jsonFile(openFileName);
    if (!jsonFile.open(QIODevice::ReadOnly))return; //should handle error here
    // Read the entire file
    QByteArray saveData = jsonFile.readAll();
    // Create QJsonDocument
    jsonDocument = QJsonDocument::fromJson(saveData);
    // From which we select an object into the current working QJsonObject
    json = jsonDocument.object();

    //load data from json file
    ui->pushButton1->setText(json["action1"].toString());
    ui->pushButton2->setText(json["action2"].toString());
    ui->pushButton3->setText(json["action3"].toString());
    ui->pushButton4->setText(json["action4"].toString());
    ui->pushButton5->setText(json["action5"].toString());
    ui->pushButton6->setText(json["action6"].toString());
    ui->pushButton7->setText(json["action7"].toString());
    ui->pushButton8->setText(json["action8"].toString());
    ui->pushButton9->setText(json["action9"].toString());
    ui->pushButton10->setText(json["action10"].toString());
    ui->pushButton11->setText(json["action11"].toString());
    ui->pushButton12->setText(json["action12"].toString());
}

void keyBindings::on_close_dialogButtonBox_accepted()
{
    event = new SDL_Event();
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Settings File"), QString(QDir::currentPath()), tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);   // Using QFileInfo
    QDir::setCurrent(fileInfo.path());  // set the current working directory where the file will be, otherwise it may not work

    // Create a file object and open it for writing.
    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))return;

    // Write the current Json object to a file.
    jsonFile.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
    jsonFile.close();   // Close file

    emit updatedKeyBindings();
}

int keyBindings::bindKey()
{
    while(SDL_PollEvent(event))
	{
	    if(event -> type == SDL_JOYBUTTONDOWN){return event->jbutton.button;}	
	}
}

void keyBindings::on_pushButton1_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action1"] = sdl;
}

void keyBindings::on_pushButton2_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action2"] = sdl;
}

void keyBindings::on_pushButton3_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action3"] = sdl;
}

void keyBindings::on_pushButton4_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action4"] = sdl;
}

void keyBindings::on_pushButton5_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action5"] = sdl;
}

void keyBindings::on_pushButton6_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action6"] = sdl;
}

void keyBindings::on_pushButton7_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action7"] = sdl;
}

void keyBindings::on_pushButton8_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action8"] = sdl;
}

void keyBindings::on_pushButton9_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action9"] = sdl;
}

void keyBindings::on_pushButton10_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action10"] = sdl;
}

void keyBindings::on_pushButton11_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action11"] = sdl;
}

void keyBindings::on_pushButton12_clicked()
{
    int button = bindKey();
    QString sdl = QString::number(button);
    json["action12"] = sdl;
}
