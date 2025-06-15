#include "mainwindow.h"
#include "./ui_mainwindow.h"
# include <QDebug>
#include <QSettings>
#include "signup.h"
#include"mainscreen.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->savedusers->setMaxVisibleItems(7);
     loadSavedUsernames();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_exitgame_button_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Tic Tac Toe", "Are you sure to close the Game?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication:: quit();
    }
    else
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(" Tic Tac Toe");
        msgBox.setTextFormat(Qt::RichText);
        msgBox.setText("<div style='font-size:18pt; font-weight:bold;'>🎉 Enjoy playing the game 😄🔥</div>");
        msgBox.setIcon(QMessageBox::NoIcon);
        QSpacerItem *spacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout layout = qobject_cast<QGridLayout>(msgBox.layout());
        if (layout)
            layout->addItem(spacer, layout->rowCount(), 0, 1, layout->columnCount());
        msgBox.exec();
    }}
    void MainWindow::on_login_button_clicked()
    {
        if (ui->password->text() == "123456789" && ui->username->text() == "Moussa")
        {
            saveUsernameIfChecked();
            QMessageBox msgBox;
            msgBox.setWindowTitle("🎉 Welcome To Tic Tac Toe");
            msgBox.setText("<div style='font-size:18pt; font-weight:bold;'>✅ Successful login</div>");
            msgBox.setIcon(QMessageBox::NoIcon);
            QSpacerItem* spacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout* layout = (QGridLayout*)msgBox.layout();
            layout->addItem(spacer, layout->rowCount(), 0, 1, layout->columnCount());
            msgBox.exec();
            this-> hide();
            MainScreen *mainscreen= new MainScreen();
            mainscreen->show();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Login Failed");
            msgBox.setText("<div style='font-size:16pt; font-weight:bold;'>❌ Invalid username or password</div>");
            msgBox.setIcon(QMessageBox::NoIcon);
            QSpacerItem* spacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
            QGridLayout* layout = (QGridLayout*)msgBox.layout();
            layout->addItem(spacer, layout->rowCount(), 0, 1, layout->columnCount());
            msgBox.exec();
        }
    }
    void MainWindow::saveUsernameIfChecked()
    {
        QString user = ui->username->text();

        if (ui->checkBox->isChecked() && !user.isEmpty()) {
            QSettings settings("savedUsernames.ini", QSettings::IniFormat);
            QStringList savedList = settings.value("usernames").toStringList();
            savedList.removeAll(user);
            savedList.append(user);
            while (savedList.size() > 20)
                savedList.removeFirst();
            settings.setValue("usernames", savedList);
            ui->savedusers->clear();
            ui->savedusers->addItems(savedList);
        }
    }
    void MainWindow::loadSavedUsernames()
    {
        QSettings settings("savedUsernames.ini", QSettings::IniFormat);
        QStringList savedList = settings.value("usernames").toStringList();
        ui->savedusers->addItems(savedList);
    }
    void MainWindow::on_savedusers_currentTextChanged(const QString &arg1)
    {
        ui->username->setText(arg1);
    }
    void MainWindow::on_signup_button_clicked()
    {
        this -> hide();
        Signup *signup = new Signup();
        signup->show();
    }