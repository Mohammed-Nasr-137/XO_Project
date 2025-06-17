#include "history.h"
#include "ui_history.h"
# include <QDebug>
#include <QSettings>
#include "signup.h"
#include"mainscreen.h"
#include "GameData.h"
History::History(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::History)
{
    ui->setupUi(this);
}

History::~History()
{
    delete ui;
}
