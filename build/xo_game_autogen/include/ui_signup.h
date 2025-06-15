/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Signup
{
public:
    QWidget *centralwidget;
    QLabel *pr_label;
    QLineEdit *username_r;
    QLabel *ur_label;
    QLineEdit *password_r;
    QLabel *signup_label;
    QPushButton *back_button;
    QPushButton *reg_button;
    QMenuBar *menubar;
    QMenu *menuregistration_on_Tic_Tac_Toe;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Signup)
    {
        if (Signup->objectName().isEmpty())
            Signup->setObjectName(QString::fromUtf8("Signup"));
        Signup->resize(488, 447);
        Signup->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background: qlineargradient(\n"
"        spread: pad,\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(0, 34, 133, 180),\n"
"        stop: 1 rgba(255, 255, 255, 80)\n"
"    );\n"
"}\n"
""));
        centralwidget = new QWidget(Signup);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pr_label = new QLabel(centralwidget);
        pr_label->setObjectName(QString::fromUtf8("pr_label"));
        pr_label->setGeometry(QRect(40, 190, 121, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        pr_label->setFont(font);
        pr_label->setStyleSheet(QString::fromUtf8("color: white;\n"
"font: 700 14pt \"Arial\";\n"
""));
        username_r = new QLineEdit(centralwidget);
        username_r->setObjectName(QString::fromUtf8("username_r"));
        username_r->setGeometry(QRect(40, 140, 201, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(false);
        username_r->setFont(font1);
        username_r->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    color: black;\n"
"    background-color: rgba(255, 255, 255, 200);  /* \330\243\330\250\331\212\330\266 \330\264\331\201\330\247\331\201 */\n"
"    border-radius: 10px;\n"
"    padding: 6px 10px;\n"
"    font: bold 12pt \"Arial\";\n"
"    border: 1px solid rgba(0, 0, 0, 50);\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #007BFF; /* \330\243\330\262\330\261\331\202 \330\254\331\205\331\212\331\204 */\n"
"    background-color: rgba(255, 255, 255, 240);\n"
"    box-shadow: 0 0 5px #007BFF;\n"
"}\n"
""));
        ur_label = new QLabel(centralwidget);
        ur_label->setObjectName(QString::fromUtf8("ur_label"));
        ur_label->setGeometry(QRect(40, 90, 121, 41));
        ur_label->setFont(font);
        ur_label->setStyleSheet(QString::fromUtf8("color: white;\n"
"font: 700 14pt \"Arial\";\n"
""));
        password_r = new QLineEdit(centralwidget);
        password_r->setObjectName(QString::fromUtf8("password_r"));
        password_r->setGeometry(QRect(40, 240, 201, 41));
        password_r->setFont(font1);
        password_r->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    color: black;\n"
"    background-color: rgba(255, 255, 255, 200);  /* \330\243\330\250\331\212\330\266 \330\264\331\201\330\247\331\201 */\n"
"    border-radius: 10px;\n"
"    padding: 6px 10px;\n"
"    font: bold 12pt \"Arial\";\n"
"    border: 1px solid rgba(0, 0, 0, 50);\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #007BFF; /* \330\243\330\262\330\261\331\202 \330\254\331\205\331\212\331\204 */\n"
"    background-color: rgba(255, 255, 255, 240);\n"
"    box-shadow: 0 0 5px #007BFF;\n"
"}\n"
""));
        password_r->setEchoMode(QLineEdit::EchoMode::Password);
        signup_label = new QLabel(centralwidget);
        signup_label->setObjectName(QString::fromUtf8("signup_label"));
        signup_label->setGeometry(QRect(40, 10, 301, 71));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(22);
        font2.setBold(true);
        font2.setItalic(false);
        signup_label->setFont(font2);
        signup_label->setStyleSheet(QString::fromUtf8("color: white;\n"
"font: 700 22pt \"Arial\";"));
        back_button = new QPushButton(centralwidget);
        back_button->setObjectName(QString::fromUtf8("back_button"));
        back_button->setGeometry(QRect(290, 320, 161, 41));
        back_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    color: white;\n"
"    background-color: rgba(0, 120, 255, 180); /* \330\243\330\262\330\261\331\202 \330\264\331\201\330\247\331\201 */\n"
"    font: bold 11pt \"Arial\";\n"
"    border-radius: 20px;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(30, 144, 255, 220); /* \330\243\330\262\330\261\331\202 \330\243\331\201\330\252\330\255 \330\271\331\206\330\257 \330\247\331\204\331\205\330\261\331\210\330\261 */\n"
"    font: bold 12pt \"Arial\";\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgba(0, 80, 180, 255); /* \330\243\330\262\330\261\331\202 \330\257\330\247\331\203\331\206 \330\271\331\206\330\257 \330\247\331\204\330\266\330\272\330\267 */\n"
"    font: bold 12pt \"Arial\";\n"
"}\n"
""));
        reg_button = new QPushButton(centralwidget);
        reg_button->setObjectName(QString::fromUtf8("reg_button"));
        reg_button->setGeometry(QRect(40, 320, 161, 41));
        reg_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    color: white;\n"
"    background-color: rgba(0, 120, 255, 180); /* \330\243\330\262\330\261\331\202 \330\264\331\201\330\247\331\201 */\n"
"    font: bold 11pt \"Arial\";\n"
"    border-radius: 20px;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(30, 144, 255, 220); /* \330\243\330\262\330\261\331\202 \330\243\331\201\330\252\330\255 \330\271\331\206\330\257 \330\247\331\204\331\205\330\261\331\210\330\261 */\n"
"    font: bold 12pt \"Arial\";\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgba(0, 80, 180, 255); /* \330\243\330\262\330\261\331\202 \330\257\330\247\331\203\331\206 \330\271\331\206\330\257 \330\247\331\204\330\266\330\272\330\267 */\n"
"    font: bold 12pt \"Arial\";\n"
"}\n"
""));
        Signup->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Signup);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 488, 25));
        menuregistration_on_Tic_Tac_Toe = new QMenu(menubar);
        menuregistration_on_Tic_Tac_Toe->setObjectName(QString::fromUtf8("menuregistration_on_Tic_Tac_Toe"));
        Signup->setMenuBar(menubar);
        statusbar = new QStatusBar(Signup);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Signup->setStatusBar(statusbar);

        menubar->addAction(menuregistration_on_Tic_Tac_Toe->menuAction());

        retranslateUi(Signup);

        QMetaObject::connectSlotsByName(Signup);
    } // setupUi

    void retranslateUi(QMainWindow *Signup)
    {
        Signup->setWindowTitle(QApplication::translate("Signup", "MainWindow", nullptr));
        pr_label->setText(QApplication::translate("Signup", "Password", nullptr));
        username_r->setPlaceholderText(QApplication::translate("Signup", "Enter Username", nullptr));
        ur_label->setText(QApplication::translate("Signup", "Username", nullptr));
        password_r->setPlaceholderText(QApplication::translate("Signup", "Enter Password", nullptr));
        signup_label->setText(QApplication::translate("Signup", "Sign Up", nullptr));
        back_button->setText(QApplication::translate("Signup", "Back", nullptr));
        reg_button->setText(QApplication::translate("Signup", "Register", nullptr));
        menuregistration_on_Tic_Tac_Toe->setTitle(QApplication::translate("Signup", "Registration on Tic Tac Toe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Signup: public Ui_Signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
