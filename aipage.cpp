#include "aipage.h"
#include "ui_aipage.h"
#include <QDebug>
#include <QSettings>
#include"mainscreen.h"
#include "GameData.h"
Aipage::Aipage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Aipage)
{
    ui->setupUi(this);
    ui->level_ai->setMaxVisibleItems(3);
    ui->start_game_ai->setEnabled(false);
    ui->turn_box_ai->addItem("❌");
    ui->turn_box_ai->addItem("⭕");
    ui->level_ai->addItem("Easy 💤");
    ui->level_ai->addItem("Medium 🧠");
    ui->level_ai->addItem("Hard 😈");
}
Aipage::~Aipage()
{
    delete ui;
}

void Aipage::on_turn_box_ai_currentTextChanged(const QString &arg1)
{   GameData::instance().box_2=true;
    GameData::instance().P1turn = arg1;
    if(arg1=="❌"){
        GameData::instance().Anotherturn ="⭕" ;
    }
    else {
        GameData::instance().Anotherturn ="❌" ;
    }
    if(GameData::instance().box_1 &&GameData::instance().box_2)
    {
        ui->start_game_ai->setEnabled(true);
    }
}
void Aipage::on_back_tomain_ai_clicked()
{
    this->hide();
    MainScreen*mainscreen=new MainScreen();
    mainscreen->show();
}
void Aipage::on_level_ai_currentTextChanged(const QString &arg1)
{    GameData::instance().level= arg1;
    qDebug()<<GameData::instance().level;
    qDebug()<<arg1;
    GameData::instance().box_1=true;
    if(GameData::instance().box_1 &&GameData::instance().box_2)
    {
        ui->start_game_ai->setEnabled(true);
    }
}

