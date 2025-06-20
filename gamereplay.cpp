#include "gamereplay.h"
#include "ui_gamereplay.h"
#include "GameData.h"
#include <QStyle>
#include "gamehistory.h"

int i = 0;

Gamereplay::Gamereplay(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gamereplay)
{

    ui->setupUi(this);
    ui->X_label->setText("X Player: "+QString::fromStdString(GameData::instance().x_player_history));
    ui->O_label->setText("O Player: "+QString::fromStdString(GameData::instance().o_player_history));
    ui->winner_label->setText("Winner: "+QString::fromStdString(GameData::instance().winner_history));

}

Gamereplay::~Gamereplay()
{
    delete ui;
}


QPushButton* Gamereplay::determine_button(int position)
{
    QPushButton* c = nullptr;

    switch (position) {
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
    return c;
}

void Gamereplay::update_icon(QPushButton* c)
{
    // QString basePath = QCoreApplication::applicationDirPath();

    QPixmap pixmap1(":/images/X.png");
    QIcon icon1(pixmap1);

    QPixmap pixmap2(":/images/O.png");
    QIcon icon2(pixmap2);
    if (i % 2 == 0) c->setIcon(icon1);
    else c->setIcon(icon2);

    c->setIconSize(QSize(150, 125));
}

void Gamereplay::on_nextButton_clicked()
{
    if (i < GameData::instance().moves_history.size())
    {
        int pos = GameData::instance().moves_history[i].first;
        string comment = GameData::instance().moves_history[i].second;
        ui->comment_label->setText(QString::fromStdString(comment));

        QPushButton* c = Gamereplay::determine_button(pos);

        Gamereplay::update_icon(c);
        if (i < GameData::instance().moves_history.size() - 1) i++;
    }
    qDebug() << i;
}


void Gamereplay::on_prevButton_clicked()
{
    if (i >= 0)
    {
        int pos = GameData::instance().moves_history[i].first;
        QPushButton* c = Gamereplay::determine_button(pos);
        c->setIcon(QIcon());
        if (i != 0) i--;
        // pos = GameData::instance().moves_history[i].first;
        string comment = GameData::instance().moves_history[i].second;
        ui->comment_label->setText(QString::fromStdString(comment));
    }
    qDebug() << i;
}


void Gamereplay::on_back_button_clicked()
{
    i = 0;
    this->hide();
    Gamehistory* gamehistory = new Gamehistory();
    gamehistory->show();
}


