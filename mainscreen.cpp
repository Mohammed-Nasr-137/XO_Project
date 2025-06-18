#include "include/mainscreen.h"
#include "include/ui_mainscreen.h"

#include <QDebug>
#include <QSettings>

#include "include/mainwindow.h"
#include "include/GameData.h"
#include "include/aipage.h"

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainScreen) {
    ui->setupUi(this);
}

MainScreen::~MainScreen() {
    delete ui;
}

void MainScreen::on_Logout_button_clicked() {
    GameData::instance().tracker = true;
    GameData::instance().secondPlayer = "";
    this->hide();
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();
}

void MainScreen::on_playAi_button_clicked() {
    GameData::instance().mode = "AI";
    this->hide();
    Aipage *aipage = new Aipage();
    aipage->show();
}

void MainScreen::on_Player_button_clicked() {
    GameData::instance().mode = "2ndPlayer";
    this->hide();
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();
}
