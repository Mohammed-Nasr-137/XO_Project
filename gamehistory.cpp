#include "gamehistory.h"
#include "ui_gamehistory.h"
#include "GameData.h"
#include "mainscreen.h"
#include "gamereplay.h"

using namespace std;

vector<tuple<int, string, string, string>> game_history;

Gamehistory::Gamehistory(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gamehistory)
{
    ui->setupUi(this);

    ui->label_9->setText("History For " + GameData::instance().firstPlayer);

    connect(ui->searchbox, &QLineEdit::textChanged, this, &Gamehistory::filterHistory);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Gamehistory::onHistoryItemClicked);

    game_history = GameData::instance().controller.GetGameHistory(GameData::instance().firstPlayer.toStdString());

    int list_id = 1;
    for (auto& game : game_history)
    {
        int game_id;
        string p1, p2, winner;

        tie(game_id, p1, p2, winner) = game;
        // qDebug() << winner;
        QString label = QString("ID: %1, 👤 %2 vs 👤 %3 - Winner🏆: %4").arg(QString::number(game_id),
                                                             QString::fromStdString(p1),
                                                             QString::fromStdString(p2),
                                                             QString::fromStdString(winner));
        QListWidgetItem* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, list_id);  // Store game_id in item
        ui->listWidget->addItem(item);
        list_id++;
    }
}

Gamehistory::~Gamehistory()
{
    delete ui;
}


void Gamehistory::filterHistory(const QString &query)
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString text = item->text();

        if (text.contains(query, Qt::CaseInsensitive)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}


void Gamehistory::onHistoryItemClicked(QListWidgetItem* item)
{
    int list_id = item->data(Qt::UserRole).toInt();

    GameData::instance().x_player_history = get<1>(game_history[list_id - 1]);
    GameData::instance().o_player_history = get<2>(game_history[list_id - 1]);
    GameData::instance().winner_history = get<3>(game_history[list_id - 1]);

    qDebug() << list_id << ", " << GameData::instance().x_player_history << ", " <<
        GameData::instance().o_player_history << ", " << GameData::instance().winner_history;

    GameData::instance().moves_history = GameData::instance().controller.LoadGameMovesWithComments(get<0>(game_history[list_id - 1]));
    this->hide();
    Gamereplay* gamerepaly = new Gamereplay();
    gamerepaly->show();
}


void Gamehistory::on_back_button_clicked()
{
    this->hide();
    MainScreen*mainscreen=new MainScreen();
    mainscreen->show();
}

