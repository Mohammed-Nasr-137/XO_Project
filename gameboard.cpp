#include "include/gameboard.h"

#include <QApplication>
#include <utility>

#include "include/ui_gameboard.h"
#include "include/mainscreen.h"
#include "include/GameData.h"

Gameboard::Gameboard(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Gameboard) {
    ui->setupUi(this);
    // display head to head stats
    if (GameData::instance().mode == "AI") {
        ui->p1_label->setText(
            "Your Turn (" + GameData::instance().P1turn + ")");
        ui->another_label->setText(
            "AI Turn (" + GameData::instance().Anotherturn + ") | " +
            GameData::instance().level + "");
        if (GameData::instance().is_ai_turn) {
            QPushButton* c;
            int ai_pos = Gameboard::make_ai_play();
            switch (ai_pos) {
            case 1: c = ui->c_1; break;
            case 2: c = ui->c_2; break;
            case 3: c = ui->c_3; break;
            case 4: c = ui->c_4; break;
            case 5: c = ui->c_5; break;
            case 6: c = ui->c_6; break;
            case 7: c = ui->c_7; break;
            case 8: c = ui->c_8; break;
            case 9: c = ui->c_9; break;
            default: c = nullptr; break;
            }
            if (c) {
                Gameboard::update_gui(c, ai_pos);
            }
        }
    } else {
        // implement multiplayer logic
        ui->p1_label->setText(
            "1st Player (" + GameData::instance().P1turn + ") : " +
            GameData::instance().firstPlayer + " ");
        ui->another_label->setText(
            "2nd Player (" + GameData::instance().Anotherturn + ") : " +
            GameData::instance().secondPlayer + " ");
    }
}

Gameboard::~Gameboard() {
    delete ui;
}

void Gameboard::on_Back_gboard_clicked() {
    this->hide();
    MainScreen *mainscreen = new MainScreen();
    mainscreen->show();
}

void Gameboard::update_gui(QPushButton* c, int pos) {
    QPixmap pixmap1("G:\\xo_game_final\\pics\\X.png");
    QIcon icon1(pixmap1);
    QPixmap pixmap2("G:\\xo_game_final\\pics\\O.png");
    QIcon icon2(pixmap2);

    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (GameData::instance().current_player == "X") {
        c->setIcon(icon1);
        GameData::instance().gui_board[row][col] = 'X';
        GameData::instance().current_player = "O";
    } else if (GameData::instance().current_player == "O") {
        c->setIcon(icon2);
        GameData::instance().gui_board[row][col] = 'O';
        GameData::instance().current_player = "X";
    }

    c->setIconSize(QSize(150, 125));
    c->setEnabled(false);

    GameData::instance().win_result =
        GameData::instance().controller.CheckWinner();
    GameData::instance().is_tie =
        GameData::instance().controller.CheckTie();
    GameData::instance().is_over =
        (GameData::instance().win_result.first ||
         GameData::instance().is_tie);

    qDebug() << GameData::instance().win_result.first
             << GameData::instance().win_result.second
             << GameData::instance().is_tie
             << GameData::instance().is_over;
}

void Gameboard::make_human_play(QPushButton* c, int pos) {
    if (GameData::instance().is_over) return;
    qDebug() << "make_human_play is called";
    GameData::instance().is_ai_turn = !GameData::instance().is_ai_turn;
    qDebug() << "Before: "
             << GameData::instance().controller.getCurrentUserSymbol()
             << ", wrapper: "
             << GameData::instance().controller.getcurrent_user();
    bool success = GameData::instance().controller.MakeHumanMove(pos);
    qDebug() << "After: "
             << GameData::instance().controller.getCurrentUserSymbol()
             << ", wrapper: "
             << GameData::instance().controller.getcurrent_user();
    if (success) {
        Gameboard::update_gui(c, pos);
        if (!GameData::instance().is_over) {
            int ai_pos = Gameboard::make_ai_play();
            QPushButton* ai_button = nullptr;
            switch (ai_pos) {
            case 1: ai_button = ui->c_1; break;
            case 2: ai_button = ui->c_2; break;
            case 3: ai_button = ui->c_3; break;
            case 4: ai_button = ui->c_4; break;
            case 5: ai_button = ui->c_5; break;
            case 6: ai_button = ui->c_6; break;
            case 7: ai_button = ui->c_7; break;
            case 8: ai_button = ui->c_8; break;
            case 9: ai_button = ui->c_9; break;
            default: break;
            }
            if (ai_button) {
                Gameboard::update_gui(ai_button, ai_pos);
            }
        }
    }
}

int Gameboard::make_ai_play() {
    qDebug() << "make_ai_play is called";
    std::pair<bool, int> p = GameData::instance().controller.MakeAIMove();
    GameData::instance().is_ai_turn = !GameData::instance().is_ai_turn;
    return p.second;
}

void Gameboard::on_c_1_clicked() {
    QPushButton* c = ui->c_1;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 1);
}

void Gameboard::on_c_2_clicked() {
    QPushButton* c = ui->c_2;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 2);
}

void Gameboard::on_c_3_clicked() {
    QPushButton* c = ui->c_3;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 3);
}

void Gameboard::on_c_4_clicked() {
    QPushButton* c = ui->c_4;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 4);
}

void Gameboard::on_c_5_clicked() {
    QPushButton* c = ui->c_5;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 5);
}

void Gameboard::on_c_6_clicked() {
    QPushButton* c = ui->c_6;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 6);
}

void Gameboard::on_c_7_clicked() {
    QPushButton* c = ui->c_7;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 7);
}

void Gameboard::on_c_8_clicked() {
    QPushButton* c = ui->c_8;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 8);
}

void Gameboard::on_c_9_clicked() {
    QPushButton* c = ui->c_9;
    qDebug() << GameData::instance().is_ai_turn;
    Gameboard::make_human_play(c, 9);
}
