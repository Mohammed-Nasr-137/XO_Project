#include "include/aipage.h"
#include "include/ui_aipage.h"
#include "include/mainscreen.h"
#include "include/GameData.h"
#include "include/gameboard.h"
#include <QDebug>
#include <QSettings>
#include <string>

Aipage::Aipage(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Aipage) {
    ui->setupUi(this);
    ui->level_ai->setMaxVisibleItems(3);
    ui->start_game_ai->setEnabled(false);
    ui->turn_box_ai->addItem("❌");
    ui->turn_box_ai->addItem("⭕");
    ui->level_ai->addItem("Easy 💤");
    ui->level_ai->addItem("Medium 🧠");
    ui->level_ai->addItem("Hard 😈");
}

Aipage::~Aipage() {
    delete ui;
}

void Aipage::on_turn_box_ai_currentTextChanged(const QString &arg1) {
    GameData::instance().box_2 = true;
    GameData::instance().P1turn = arg1;
    if (arg1 == "❌") {
        GameData::instance().Anotherturn = "⭕";
        GameData::instance().p1_move = "X";
        GameData::instance().current_player = "X";
        GameData::instance().is_ai_turn = false;
    } else {
        qDebug() << "I'm here";
        GameData::instance().Anotherturn = "❌";
        GameData::instance().p1_move = "O";
        GameData::instance().current_player = "X";
        GameData::instance().is_ai_turn = true;
    }
    if (GameData::instance().box_1 && GameData::instance().box_2) {
        ui->start_game_ai->setEnabled(true);
    }
}

void Aipage::on_back_tomain_ai_clicked() {
    this->hide();
    MainScreen *mainscreen = new MainScreen();
    mainscreen->show();
}

void Aipage::on_level_ai_currentTextChanged(const QString &arg1) {
    GameData::instance().level = arg1;
    GameData::instance().box_1 = true;

    if (arg1 == "Easy 💤") {
        GameData::instance().ai_difficulty = "easy";
    } else if (arg1 == "Medium 🧠") {
        GameData::instance().ai_difficulty = "medium";
    } else if (arg1 == "Hard 😈") {
        GameData::instance().ai_difficulty = "hard";
    }

    if (GameData::instance().box_1 && GameData::instance().box_2) {
        ui->start_game_ai->setEnabled(true);
    }
}

void Aipage::on_start_game_ai_clicked() {
    this->hide();
    GameData::instance().controller.StartNewGame(
        GameData::instance().firstPlayer.toStdString(),
        "AI",
        true,
        GameData::instance().ai_difficulty,
        GameData::instance().p1_move.toStdString());
    Gameboard *gameboard = new Gameboard();
    gameboard->show();
}

void Aipage::on_level_ai_activated(int index) {
}

void Aipage::on_level_ai_currentIndexChanged(int index) {
}
