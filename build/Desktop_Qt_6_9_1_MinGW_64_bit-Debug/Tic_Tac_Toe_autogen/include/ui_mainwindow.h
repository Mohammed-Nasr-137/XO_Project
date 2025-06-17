/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *username;
    QLabel *label;
    QPushButton *signup_button;
    QLabel *Login_Label;
    QComboBox *savedusers;
    QLabel *label_2;
    QLineEdit *password;
    QCheckBox *checkBox;
    QPushButton *login_button;
    QPushButton *exitgame_button;
    QMenuBar *menubar;
    QMenu *menuTic_Tac_Toe;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(473, 531);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background: qlineargradient(\n"
"        spread: pad,\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(0, 34, 133, 180),\n"
"        stop: 1 rgba(255, 255, 255, 80)\n"
"    );\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        username = new QLineEdit(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(40, 140, 201, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        username->setFont(font);
        username->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 90, 121, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(false);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: white;\n"
"font: 700 14pt \"Arial\";\n"
""));
        signup_button = new QPushButton(centralwidget);
        signup_button->setObjectName("signup_button");
        signup_button->setGeometry(QRect(270, 360, 161, 41));
        signup_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        Login_Label = new QLabel(centralwidget);
        Login_Label->setObjectName("Login_Label");
        Login_Label->setGeometry(QRect(40, 0, 301, 71));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(22);
        font2.setBold(true);
        font2.setItalic(false);
        Login_Label->setFont(font2);
        Login_Label->setStyleSheet(QString::fromUtf8("color: white;\n"
"font: 700 22pt \"Arial\";"));
        savedusers = new QComboBox(centralwidget);
        savedusers->setObjectName("savedusers");
        savedusers->setGeometry(QRect(270, 140, 161, 41));
        savedusers->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: rgba(220, 220, 220, 180);  /* \330\261\331\205\330\247\330\257\331\212 \331\201\330\247\330\252\330\255 */\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 6px 10px;\n"
"    font: bold 11pt \"Arial\";\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    background-color: rgba(245, 245, 245, 220);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 25px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: rgba(240, 240, 240, 230);\n"
"    color: black;\n"
"    border: none;\n"
"    selection-background-color: rgba(100, 149, 237, 50); /* \330\270\331\204 \330\243\330\262\330\261\331\202 \331\201\330\247\330\252\330\255 */\n"
"}\n"
""));
        savedusers->setDuplicatesEnabled(false);
        savedusers->setFrame(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 190, 121, 51));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: white;\n"
"font: 700 14pt \"Arial\";\n"
""));
        password = new QLineEdit(centralwidget);
        password->setObjectName("password");
        password->setGeometry(QRect(40, 240, 201, 41));
        password->setFont(font);
        password->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        password->setEchoMode(QLineEdit::EchoMode::Password);
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(40, 310, 181, 31));
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    spacing: 8px;\n"
"    color: white;\n"
"    font: bold 11pt \"Arial\";\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    border-radius: 3px;\n"
"    border: 2px solid white;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background-color:  rgb(0, 170, 255);\n"
"	\n"
"  \n"
"}\n"
""));
        login_button = new QPushButton(centralwidget);
        login_button->setObjectName("login_button");
        login_button->setGeometry(QRect(40, 360, 161, 41));
        login_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        exitgame_button = new QPushButton(centralwidget);
        exitgame_button->setObjectName("exitgame_button");
        exitgame_button->setGeometry(QRect(160, 430, 151, 41));
        exitgame_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 473, 25));
        menuTic_Tac_Toe = new QMenu(menubar);
        menuTic_Tac_Toe->setObjectName("menuTic_Tac_Toe");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTic_Tac_Toe->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        username->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Username", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        signup_button->setText(QCoreApplication::translate("MainWindow", "SignUp", nullptr));
        Login_Label->setText(QCoreApplication::translate("MainWindow", "Login     ", nullptr));
        savedusers->setPlaceholderText(QCoreApplication::translate("MainWindow", "     Saved Users", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Password", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Remeber me", nullptr));
        login_button->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        exitgame_button->setText(QCoreApplication::translate("MainWindow", "EXIT GAME", nullptr));
        menuTic_Tac_Toe->setTitle(QCoreApplication::translate("MainWindow", "Tic Tac Toe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
