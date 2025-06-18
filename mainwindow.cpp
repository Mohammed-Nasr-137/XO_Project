#include "include/mainwindow.h"

#include <QDebug>
#include <QSettings>

#include "include/signup.h"
#include "include/mainscreen.h"
#include "include/GameData.h"
#include "include/turnpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);
    if (!GameData::instance().tracker) {
        ui->Login_Label->setText("Second Player Login");
        ui->exitgame_button->setText("Back to Main");
    } else {
        ui->exitgame_button->setText("Exit Game");
        ui->Login_Label->setText("Login");
    }
    ui->savedusers->setMaxVisibleItems(7);
    loadSavedUsernames();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_exitgame_button_clicked() {
    if (GameData::instance().tracker) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this, "Tic Tac Toe",
            "Are you sure to close the Game?",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QApplication::quit();
        } else {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle(" Tic Tac Toe");
            msgBox.setTextFormat(Qt::RichText);
            msgBox.setText(
                "<div style='font-size:18pt; font-weight:bold;'>🎉 Enjoy playing "
                "the game 😄🔥</div>");
            msgBox.setIcon(QMessageBox::NoIcon);
            QSpacerItem *spacer = new QSpacerItem(
                400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout *layout = reinterpret_cast<QGridLayout*>(msgBox.layout());
            if (layout) {
                layout->addItem(
                    spacer, layout->rowCount(), 0, 1, layout->columnCount());
            }
            msgBox.exec();
        }
    } else {
        this->hide();
        MainScreen *mainscreen = new MainScreen();
        mainscreen->show();
    }
}

void MainWindow::on_login_button_clicked() {
    QString username = ui->username->text();
    QString password = ui->password->text();
    if (GameData::instance().controller.Login_Wrapper(
            username.toStdString(), password.toStdString())) {
        if (GameData::instance().tracker) {
            GameData::instance().firstPlayer = username;
        } else {
            GameData::instance().secondPlayer = username;
        }
        if (GameData::instance().secondPlayer ==
            GameData::instance().firstPlayer) {
            QMessageBox::information(
                this, "Duplicate User", "Enter a different user.");
        } else {
            saveUsernameIfChecked();
            QMessageBox msgBox;
            msgBox.setWindowTitle("🎉 Welcome To Tic Tac Toe");
            msgBox.setText(
                "<div style='font-size:18pt; font-weight:bold;'>✅ Successful "
                "login</div>");
            msgBox.setIcon(QMessageBox::NoIcon);
            QSpacerItem* spacer = new QSpacerItem(
                400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout* layout =
                reinterpret_cast<QGridLayout*>(msgBox.layout());
            layout->addItem(
                spacer, layout->rowCount(), 0, 1, layout->columnCount());
            msgBox.exec();
            if (GameData::instance().tracker) {
                GameData::instance().tracker = false;
                this->hide();
                MainScreen *mainscreen = new MainScreen();
                mainscreen->show();
            } else {
                this->hide();
                Turnpage *turnpage = new Turnpage();
                turnpage->show();
            }
        }
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Login Failed");
        msgBox.setText(
            "<div style='font-size:16pt; font-weight:bold;'>❌ Invalid username "
            "or password</div>");
        msgBox.setIcon(QMessageBox::NoIcon);
        QSpacerItem* spacer = new QSpacerItem(
            400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout =
            reinterpret_cast<QGridLayout*>(msgBox.layout());
        layout->addItem(
            spacer, layout->rowCount(), 0, 1, layout->columnCount());
        msgBox.exec();
    }
}

void MainWindow::saveUsernameIfChecked() {
    QString user = ui->username->text();

    if (ui->checkBox->isChecked() && !user.isEmpty()) {
        QSettings settings("savedUsernames.ini", QSettings::IniFormat);
        QStringList savedList = settings.value("usernames").toStringList();
        savedList.removeAll(user);
        savedList.append(user);
        while (savedList.size() > 20) {
            savedList.removeFirst();
        }
        settings.setValue("usernames", savedList);
        ui->savedusers->clear();
        ui->savedusers->addItems(savedList);
    }
}

void MainWindow::loadSavedUsernames() {
    QSettings settings("savedUsernames.ini", QSettings::IniFormat);
    QStringList savedList = settings.value("usernames").toStringList();
    ui->savedusers->addItems(savedList);
}

void MainWindow::on_savedusers_currentTextChanged(const QString &arg1) {
    ui->username->setText(arg1);
}

void MainWindow::on_signup_button_clicked() {
    this->hide();
    Signup *signup = new Signup();
    signup->show();
}
