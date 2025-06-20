#include "gameboard.h"
#include "ui_gameboard.h"
#include"mainscreen.h"
#include "GameData.h"
#include <QApplication>
#include <QStyle>
#include <QTimer>
#include "state.h"
#include <QProgressBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>

#define delay 100


// QApplication icon();


Gameboard::Gameboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    // display head to head stats
    Gameboard::on_Reset_button_clicked();
    Gameboard::get_head_to_head_stats();
    if (GameData::instance().is_p1_starts)
    {
        ui->p1_label->setProperty("active", true);
        ui->another_label->setProperty("active", false);
    }
    else
    {
        ui->p1_label->setProperty("active", false);
        ui->another_label->setProperty("active", true);
    }
    /*
    QWidget *containerWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(containerWidget);
    layout->addWidget(ui->progressBar_7);
    containerWidget->setLayout(layout);

    // 2. Create a QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene();

    // 3. Create a QGraphicsProxyWidget and embed the progress bar
    QGraphicsProxyWidget *proxy = scene->addWidget(containerWidget);

    // 4. Set the rotation (e.g., 45 degrees clockwise)
    proxy->setRotation(45);
    // You can also set the origin for rotation (defaults to top-left of the item)
    // proxy->setTransformOriginPoint(containerWidget->width() / 2, containerWidget->height() / 2);

    // 5. Create a QGraphicsView to display the scene
    // QGraphicsView *view = new QGraphicsView(scene);
    // view->setRenderHint(QPainter::Antialiasing); // For smoother rendering
    // view->setWindowTitle("Rotated Progress Bar");
    // view->resize(400, 300);
    // view->show();


     QGraphicsScene *prog = new QGraphicsScene;
    QGraphicsProxyWidget *proxy = ui->progressBar_7;
    // Apply rotation (only)
    QTransform progressBar_7;
    progressBar_7.rotate(45);  // Rotate by 45 degrees
    proxy->setTransform(progressBar_7)*/;

    GameData::instance().win_result = {false, "", 0};   // <is_win, winner_move>
    GameData::instance().is_tie = false;
    GameData::instance().is_over = false;

    if(GameData::instance().mode=="AI")
    {
        ui->p1_label->setText("Your Turn ("+GameData::instance().P1turn+")");
        ui->another_label->setText("AI Turn ("+GameData::instance().Anotherturn+") | "+GameData::instance().level+"");
        if (GameData::instance().is_ai_turn)
        {
            QPushButton* c;
            int ai_pos = Gameboard::make_ai_play();
            switch (ai_pos) {
            case 1:
                c = ui->c_1;
                break;
            case 2:
                c = ui->c_2;
                break;
            case 3:
                c = ui->c_3;
                break;
            case 4:
                c = ui->c_4;
                break;
            case 5:
                c = ui->c_5;
                break;
            case 6:
                c = ui->c_6;
                break;
            case 7:
                c = ui->c_7;
                break;
            case 8:
                c = ui->c_8;
                break;
            case 9:
                c = ui->c_9;
                break;
            }
            Gameboard::update_gui(c, ai_pos);
        }
    }
    else
    {
        // implement multiplayer logic
        ui->p1_label->setText("1st Player ("+GameData::instance().P1turn+") : "+GameData::instance().firstPlayer+" ");
        ui->another_label->setText("2nd Player ("+GameData::instance().Anotherturn+") : "+GameData::instance().secondPlayer+" ");
    }
}

Gameboard::~Gameboard()
{
    delete ui;
}


void Gameboard::get_head_to_head_stats()
{
    bool is_single = (GameData::instance().mode == "AI") ? true : false;
    tuple<int, int ,int> stats = {0, 0, 0};
    if (is_single)
    {
        stats = GameData::instance().controller.GetHumanVsAIStats(GameData::instance().firstPlayer.toStdString());
    }
    else
    {
        stats = GameData::instance().controller.GetHeadToHeadStats(GameData::instance().firstPlayer.toStdString(), GameData::instance().secondPlayer.toStdString());
    }

    ui->p1_wins_label->setText(GameData::instance().firstPlayer+" wins: "+QString::number(get<0>(stats)));
    ui->p2_wins_label->setText(GameData::instance().secondPlayer+" wins: "+QString::number(get<1>(stats)));
    ui->ties_label->setText("Ties: "+QString::number(get<2>(stats)));

    // qDebug() << "before";

    if (get<0>(stats) > get<1>(stats))
    {
        // qDebug() << "case1";
        ui->p1_wins_label->setProperty("status", "win");
        ui->p1_wins_label->style()->unpolish(ui->p1_wins_label);
        ui->p1_wins_label->style()->polish(ui->p1_wins_label);

        ui->p2_wins_label->setProperty("status", "lose");
        ui->p2_wins_label->style()->unpolish(ui->p2_wins_label);
        ui->p2_wins_label->style()->polish(ui->p2_wins_label);
    }
    else if (get<0>(stats) < get<1>(stats))
    {
        // qDebug() << "case2";
        ui->p1_wins_label->setProperty("status", "lose");
        ui->p1_wins_label->style()->unpolish(ui->p1_wins_label);
        ui->p1_wins_label->style()->polish(ui->p1_wins_label);

        ui->p2_wins_label->setProperty("status", "win");
        ui->p2_wins_label->style()->unpolish(ui->p2_wins_label);
        ui->p2_wins_label->style()->polish(ui->p2_wins_label);
    }

    else
    {
        // qDebug() << "case3";
        ui->p1_wins_label->setProperty("status", "draw");
        ui->p1_wins_label->style()->unpolish(ui->p1_wins_label);
        ui->p1_wins_label->style()->polish(ui->p1_wins_label);

        ui->p2_wins_label->setProperty("status", "draw");
        ui->p2_wins_label->style()->unpolish(ui->p2_wins_label);
        ui->p2_wins_label->style()->polish(ui->p2_wins_label);
    }
}


void Gameboard::on_Back_gboard_clicked()
{
    Gameboard::on_Reset_button_clicked();
    this->hide();
    MainScreen*mainscreen=new MainScreen();
    mainscreen->show();
}


void Gameboard::update_label()
{
    if (GameData::instance().current_player == GameData::instance().p1_move)
    {
        // qDebug() << "switcher1";
        ui->p1_label->setProperty("active", true);
        ui->another_label->setProperty("active", false);

        ui->p1_label->style()->unpolish(ui->p1_label);
        ui->p1_label->style()->polish(ui->p1_label);

        ui->another_label->style()->unpolish(ui->another_label);
        ui->another_label->style()->polish(ui->another_label);
    }
    else
    {
        // qDebug() << "switcher2";
        ui->p1_label->setProperty("active", false);
        ui->another_label->setProperty("active", true);

        ui->p1_label->style()->unpolish(ui->p1_label);
        ui->p1_label->style()->polish(ui->p1_label);

        ui->another_label->style()->unpolish(ui->another_label);
        ui->another_label->style()->polish(ui->another_label);
    }
}


void Gameboard::update_gui(QPushButton* c, int pos)
{
    QPixmap pixmap1(":/images/X.png");
    QIcon icon1(pixmap1);

    QPixmap pixmap2(":/images/O.png");
    QIcon icon2(pixmap2);

    string comment = (GameData::instance().mode == "AI" && !GameData::instance().is_ai_turn) ? GameData::instance().controller.GetComment() : "Human Move";
    GameData::instance().stack_last_played_pos.push_back({pos, comment});
    // GameData::instance().last_played_button = c;

    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (GameData::instance().current_player == "X")
    {
        // qDebug() << "enter";
        c->setIcon(icon1);
        GameData::instance().gui_board[row][col] = 'X';   // change index
        GameData::instance().current_player = "O";
    }
    else if (GameData::instance().current_player == "O")
    {
        c->setIcon(icon2);
        GameData::instance().gui_board[row][col] = 'O';  // change index
        GameData::instance().current_player = "X";
    }

    c->setIconSize(QSize(150, 125));
    c->setEnabled(false);

    Gameboard::update_label();

    GameData::instance().win_result = GameData::instance().controller.CheckWinner();
    GameData::instance().is_tie = GameData::instance().controller.CheckTie();
    GameData::instance().is_over = (get<0>(GameData::instance().win_result) || GameData::instance().is_tie);

    if (GameData::instance().is_over)
    {
        QString x_player = (GameData::instance().p1_move == "X") ? GameData::instance().firstPlayer : GameData::instance().secondPlayer;
        QString o_player = (GameData::instance().p1_move == "X") ? GameData::instance().secondPlayer : GameData::instance().firstPlayer;
        string winner = (get<0>(GameData::instance().win_result)) ? get<1>(GameData::instance().win_result) : "Tie";
        if (GameData::instance().controller.SaveGameWithMoves(x_player.toStdString(), o_player.toStdString(),
                                                              winner, GameData::instance().stack_last_played_pos))
        // this-> hide();
        Gameboard::get_head_to_head_stats();
        GameData::instance().gameboard_end = this;
        State*state=new State ();
        state->show();
    }

    // qDebug() << get<0>(GameData::instance().win_result) << get<1>(GameData::instance().win_result) << get<2>(GameData::instance().win_result)
    //         << GameData::instance().is_tie << GameData::instance().is_over;
}


void Gameboard::handleAiTurnDelayed()
{
    if (!GameData::instance().is_over && GameData::instance().mode == "AI")
    {
        QPushButton* c;
        int ai_pos = Gameboard::make_ai_play();
        switch (ai_pos) {
        case 1:
            c = ui->c_1;
            break;
        case 2:
            c = ui->c_2;
            break;
        case 3:
            c = ui->c_3;
            break;
        case 4:
            c = ui->c_4;
            break;
        case 5:
            c = ui->c_5;
            break;
        case 6:
            c = ui->c_6;
            break;
        case 7:
            c = ui->c_7;
            break;
        case 8:
            c = ui->c_8;
            break;
        case 9:
            c = ui->c_9;
            break;
        }
        Gameboard::update_gui(c, ai_pos);
    }
}


void Gameboard::make_human_play(QPushButton* c, int pos)
{
    if (GameData::instance().is_over) return; // put here logic for after game effects (line at winning pattern, winner window, save data)


    qDebug() << "make_human_play is called";
    GameData::instance().is_ai_turn = !GameData::instance().is_ai_turn;
    // qDebug() << "Before: " << GameData::instance().controller.getCurrentUserSymbol() << ", wrapper: " << GameData::instance().controller.getcurrent_user();

    bool success = GameData::instance().controller.MakeHumanMove(pos);
    // qDebug() << success;
    // qDebug() << "After: " << GameData::instance().controller.getCurrentUserSymbol() << ", wrapper: " << GameData::instance().controller.getcurrent_user();
    if (success)
    {
        Gameboard::update_gui(c, pos);
        QTimer::singleShot(delay, this, &Gameboard::handleAiTurnDelayed);
        // qDebug() << "After gui: " << GameData::instance().controller.getCurrentUserSymbol() << ", wrapper: " << GameData::instance().controller.getcurrent_user();

    }
}


int Gameboard::make_ai_play()
{
    qDebug() << "make_ai_play is called";
    pair<bool, int> p = GameData::instance().controller.MakeAIMove();
    GameData::instance().is_ai_turn = !GameData::instance().is_ai_turn;
    return p.second;
}


void Gameboard::on_c_1_clicked()
{
    QPushButton* c = ui->c_1;

    // qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 1);
    // if (!GameData::instance().is_ai_turn) Gameboard::make_human_play(1);  // change pos

    // GameData::instance().is_ai_turn = !GameData::instance().is_ai_turn;

    /*if (GameData::instance().is_ai_turn)
    {
        Gameboard::make_ai_play();
        // GameData::instance().is_ai_turn = !GameData::instance().is_ai_turn;
    }*/
}


void Gameboard::on_c_2_clicked()
{
    QPushButton* c = ui->c_2;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 2);
}


void Gameboard::on_c_3_clicked()
{
    QPushButton* c = ui->c_3;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 3);
}


void Gameboard::on_c_4_clicked()
{
    QPushButton* c = ui->c_4;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 4);
}


void Gameboard::on_c_5_clicked()
{
    QPushButton* c = ui->c_5;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 5);
}


void Gameboard::on_c_6_clicked()
{
    QPushButton* c = ui->c_6;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 6);
}


void Gameboard::on_c_7_clicked()
{
    QPushButton* c = ui->c_7;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 7);
}


void Gameboard::on_c_8_clicked()
{
    QPushButton* c = ui->c_8;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 8);
}


void Gameboard::on_c_9_clicked()
{
    QPushButton* c = ui->c_9;

    qDebug() << GameData::instance().is_ai_turn;

    Gameboard::make_human_play(c, 9);
}


void Gameboard::on_Reset_button_clicked()
{
    // qDebug() << "in reset, before: " << GameData::instance().is_ai_turn;
    bool is_single = (GameData::instance().mode == "AI") ? true : false;
    GameData::instance().current_player = "X";
    GameData::instance().controller.StartNewGame(GameData::instance().firstPlayer.toStdString(), GameData::instance().secondPlayer.toStdString(), is_single, GameData::instance().ai_difficulty, GameData::instance().current_player);
    GameData::instance().win_result = {false, "", 0};   // <is_win, winner_move>
    GameData::instance().is_tie = false;
    GameData::instance().is_over = false;
    GameData::instance().is_ai_turn = (is_single && (GameData::instance().p1_move == "O"));

    qDebug() << GameData::instance().is_ai_turn;

    ui->c_1->setIcon(QIcon());
    ui->c_2->setIcon(QIcon());
    ui->c_3->setIcon(QIcon());
    ui->c_4->setIcon(QIcon());
    ui->c_5->setIcon(QIcon());
    ui->c_6->setIcon(QIcon());
    ui->c_7->setIcon(QIcon());
    ui->c_8->setIcon(QIcon());
    ui->c_9->setIcon(QIcon());

    ui->c_1->setEnabled(true);
    ui->c_2->setEnabled(true);
    ui->c_3->setEnabled(true);
    ui->c_4->setEnabled(true);
    ui->c_5->setEnabled(true);
    ui->c_6->setEnabled(true);
    ui->c_7->setEnabled(true);
    ui->c_8->setEnabled(true);
    ui->c_9->setEnabled(true);

    while (!GameData::instance().stack_last_played_pos.empty())
    {
        GameData::instance().stack_last_played_pos.pop_back();
    }

    Gameboard::update_label();

    if (GameData::instance().is_ai_turn) {
        QPushButton* c;
        int ai_pos = Gameboard::make_ai_play();
        switch (ai_pos) {
        case 1:
            c = ui->c_1;
            break;
        case 2:
            c = ui->c_2;
            break;
        case 3:
            c = ui->c_3;
            break;
        case 4:
            c = ui->c_4;
            break;
        case 5:
            c = ui->c_5;
            break;
        case 6:
            c = ui->c_6;
            break;
        case 7:
            c = ui->c_7;
            break;
        case 8:
            c = ui->c_8;
            break;
        case 9:
            c = ui->c_9;
            break;
        }
        Gameboard::update_gui(c, ai_pos);
    }

    // qDebug() << "in reset, after: " << GameData::instance().is_ai_turn;
}


void Gameboard::on_undo_clicked()
{
    if (!GameData::instance().stack_last_played_pos.empty() && !GameData::instance().is_over)
    {
        bool is_single = (GameData::instance().mode == "AI") ? true : false;
        // qDebug() << "in undo, before: " << GameData::instance().is_ai_turn;
        int i = 1;
        if (!GameData::instance().is_ai_turn && is_single && (GameData::instance().stack_last_played_pos.size() >= 1) )
        {
            qDebug() << "entered";
            i = 2;
        }
        for (; i > 0; i--)
        {
            qDebug() << i << ", "<< GameData::instance().is_ai_turn << ", " << GameData::instance().stack_last_played_pos.empty();
            if (!GameData::instance().stack_last_played_pos.empty())
            {
                GameData::instance().current_player = (GameData::instance().current_player == "X") ? "O" : "X";

                GameData::instance().controller.Undo();

                Gameboard::update_label();

                // GameData::instance().win_result = {false, ""};   // <is_win, winner_move>
                // GameData::instance().is_tie = false;
                // GameData::instance().is_over = false;
                // GameData::instance().is_ai_turn = is_single;

                int last_pos = GameData::instance().stack_last_played_pos.back().first;

                switch (last_pos) {
            case 1:
                GameData::instance().last_played_button = ui->c_1;
                break;
            case 2:
                GameData::instance().last_played_button = ui->c_2;
                break;
            case 3:
                GameData::instance().last_played_button = ui->c_3;
                break;
            case 4:
                GameData::instance().last_played_button = ui->c_4;
                break;
            case 5:
                GameData::instance().last_played_button = ui->c_5;
                break;
            case 6:
                GameData::instance().last_played_button = ui->c_6;
                break;
            case 7:
                GameData::instance().last_played_button = ui->c_7;
                break;
            case 8:
                GameData::instance().last_played_button = ui->c_8;
                break;
            case 9:
                GameData::instance().last_played_button = ui->c_9;
                break;
            }

                int row = (last_pos - 1) / 3;
                int col = (last_pos - 1) % 3;

                GameData::instance().gui_board[row][col] = ' ';
                GameData::instance().last_played_button->setIcon(QIcon());
                GameData::instance().last_played_button->setEnabled(true);

                GameData::instance().stack_last_played_pos.pop_back();
            }
            else
            {
                Gameboard::on_Reset_button_clicked();
                qDebug() << "else has called reset";
            }
            // qDebug() << "in undo, after: " << GameData::instance().is_ai_turn;
        }
    }
    else
    {
        // implement can't undo logic when board is empty or game over
        QMessageBox::warning(this, "Not Valid", "You can't Undo.");
    }
}

