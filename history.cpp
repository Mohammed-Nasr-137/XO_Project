#include "include/history.h"

#include <QDebug>
#include <QSettings>

#include "include/ui_history.h"
#include "include/signup.h"
#include "include/mainscreen.h"
#include "include/GameData.h"

History::History(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::History) {
    ui->setupUi(this);
}

History::~History() {
    delete ui;
}
