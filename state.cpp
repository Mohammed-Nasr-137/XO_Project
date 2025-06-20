#include "state.h"
#include "ui_state.h"
#include "mainscreen.h"
#include "GameData.h"
#include "turnpage.h"
#include "aipage.h"
// #include "gameboard.h"
#include <QString>

State::State(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::State)
{
    ui->setupUi(this);

    if (get<0>(GameData::instance().win_result))
    {
        QString winner = (get<1>(GameData::instance().win_result) ==
                          GameData::instance().p1_move) ? GameData::instance().firstPlayer : GameData::instance().secondPlayer;
        QString loser = (get<1>(GameData::instance().win_result) ==
                          GameData::instance().p1_move) ? GameData::instance().secondPlayer : GameData::instance().firstPlayer;
        ui->winnerlabel->setText(winner+" Wins 🏆🎉 | "+ loser+ " Lost ❌😞");
    }
    else if (GameData::instance().is_tie)
    {
        ui->winnerlabel->setText("Tie ⚖️");
    }
    // Gameboard::on_Reset_button_clicked();
}

State::~State()
{
    delete ui;
}




void State::on_playagain_clicked()
{
    // GameData::instance().current_player = "X";
    GameData::instance().gameboard_end->hide();
    this->hide();
    if (GameData::instance().mode == "AI")
    {
        Aipage* aipage = new Aipage();
        aipage->show();
    }
    else
    {
        Turnpage* turnpage = new Turnpage();
        turnpage->show();
    }


    // Gameboard*gameboard= new Gameboard();
    // gameboard->show();
}


void State::on_MainMenust_clicked()
{
    GameData::instance().gameboard_end->hide();
    this->hide();
    MainScreen*mainscreen=new MainScreen();
    mainscreen->show();
}


