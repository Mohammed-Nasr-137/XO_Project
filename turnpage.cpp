#include "include/turnpage.h"
#include <QDebug>
#include <QSettings>
#include "include/ui_turnpage.h"
#include"include/mainscreen.h"
#include "include/GameData.h"
#include"#include/gameboard.h"

Turnpage::Turnpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Turnpage)
{
    ui->setupUi(this);
    ui->start_game->setEnabled(false);
    ui->turn_box->addItem("❌");
    ui->turn_box->addItem("⭕");
}
Turnpage::~Turnpage()
{
    delete ui;
}
void Turnpage::on_back_tomain_p_clicked()
{
    this->hide();
    MainScreen*mainscreen = new MainScreen();
    mainscreen->show();
}
void Turnpage::on_turn_box_currentTextChanged(const QString &arg1)
{
    GameData::instance().P1turn = arg1;
    if (arg1 == "❌"){
        GameData::instance().Anotherturn ="⭕";
        GameData::instance().p1_move = "X";
    }else {
        GameData::instance().Anotherturn ="❌";
        GameData::instance().p1_move = "O";
    }
   ui->start_game->setEnabled(true);
}

void Turnpage::on_start_game_clicked()
{
    this->hide();
    Gameboard*gameboard = new Gameboard();
    gameboard->show();
}


void Turnpage::on_turn_box_activated(int index)
{

}

