#include "signup.h"
#include "ui_signup.h"
# include <QDebug>
#include <QSettings>
#include"mainwindow.h"
Signup::Signup(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
}
Signup::~Signup()
{
    delete ui;
}
void Signup::on_reg_button_clicked()
{
    bool check=true;
    QString username = ui->username_r->text();
    QString password = ui->password_r->text();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "⚠️ Username cannot be empty");
        check =false ;
    }
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "⚠️ Password cannot be empty");
        check =false ;
    }
    if (password.length() <= 3) {
        QMessageBox::warning(this, "Input Error", " ⚠️Password must be more than 3 characters");
        check =false ;
    }
    if (check)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Successful Registration ");
        msgBox.setText("<div style='font-size:18pt; font-weight:bold;'>✅ Successful Registration</div>");
        msgBox.setIcon(QMessageBox::NoIcon);
        QSpacerItem* spacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = (QGridLayout*)msgBox.layout();
        layout->addItem(spacer, layout->rowCount(), 0, 1, layout->columnCount());
        msgBox.exec();
        this->hide();
        MainWindow*mainwindow=new MainWindow();
        mainwindow->show();
    }
}
void Signup::on_back_button_clicked()
{
    this->hide();
    MainWindow*mainwindow=new MainWindow();
    mainwindow->show();
}
