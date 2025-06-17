/********************************************************************************
** Form generated from reading UI file 'turnpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURNPAGE_H
#define UI_TURNPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Turnpage
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox_p;
    QPushButton *start_game;
    QPushButton *back_tomain_p;
    QLabel *turn_label;
    QComboBox *turn_box;
    QGroupBox *groupBox_p_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Turnpage)
    {
        if (Turnpage->objectName().isEmpty())
            Turnpage->setObjectName("Turnpage");
        Turnpage->resize(391, 268);
        Turnpage->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background: qlineargradient(\n"
"        spread: pad,\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(0, 34, 133, 180),\n"
"        stop: 1 rgba(255, 255, 255, 80)\n"
"    );\n"
"}\n"
""));
        centralwidget = new QWidget(Turnpage);
        centralwidget->setObjectName("centralwidget");
        groupBox_p = new QGroupBox(centralwidget);
        groupBox_p->setObjectName("groupBox_p");
        groupBox_p->setGeometry(QRect(10, 140, 201, 111));
        groupBox_p->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: none;\n"
"}\n"
""));
        groupBox_p->setFlat(false);
        groupBox_p->setCheckable(false);
        groupBox_p->setChecked(false);
        start_game = new QPushButton(groupBox_p);
        start_game->setObjectName("start_game");
        start_game->setGeometry(QRect(30, 50, 141, 41));
        start_game->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"\n"
"QPushButton:disabled {\n"
"    background-color: rgba(150, 150, 150, 100); /* \330\261\331\205\330\247\330\257\331\212 \331\201\330\247\330\252\330\255 \330\264\331\201\330\247\331\201 */\n"
"    color: rgba(255, 255, "
                        "255, 180); /* \330\243\330\250\331\212\330\266 \330\250\330\247\331\207\330\252 */\n"
"    font: bold 11pt \"Arial\";\n"
"}\n"
""));
        back_tomain_p = new QPushButton(centralwidget);
        back_tomain_p->setObjectName("back_tomain_p");
        back_tomain_p->setGeometry(QRect(210, 190, 141, 41));
        back_tomain_p->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        turn_label = new QLabel(centralwidget);
        turn_label->setObjectName("turn_label");
        turn_label->setGeometry(QRect(-60, -10, 501, 81));
        turn_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: qlineargradient(\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(30, 60, 114, 150),   /* Dark Blue with transparency */\n"
"        stop: 1 rgba(42, 82, 152, 150)    /* Medium Blue with transparency */\n"
"    );\n"
"    color: white;\n"
"    font: bold 20pt \"Segoe UI\";\n"
"    padding: 14px;\n"
"    border-radius: 20px;\n"
"    border: 2px solid rgba(255, 255, 255, 180); /* Semi-transparent white border */\n"
"    qproperty-alignment: AlignCenter;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    background-color: qlineargradient(\n"
"        x1: 1, y1: 0,\n"
"        x2: 0, y2: 1,\n"
"        stop: 0 rgba(58, 28, 113, 180),   /* Dark purple */\n"
"        stop: 1 rgba(215, 109, 119, 180)  /* Pink with transparency */\n"
"    );\n"
"    color: #FFEB3B;\n"
"    border: 2px solid #FFEB3B;\n"
"}\n"
""));
        turn_box = new QComboBox(centralwidget);
        turn_box->setObjectName("turn_box");
        turn_box->setEnabled(true);
        turn_box->setGeometry(QRect(120, 90, 151, 41));
        turn_box->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                      stop:0 #e0f7fa, stop:1 #b2ebf2); /* gradient blue */\n"
"    color: #004d40; /* deep teal text */\n"
"    border: 2px solid #4dd0e1;\n"
"    border-radius: 12px;\n"
"    padding: 8px 12px;\n"
"    font: bold 12pt \"Segoe UI\";\n"
"    qproperty-alignment: AlignCenter; /* center text */\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    background-color: #b2ebf2;\n"
"    border: 2px solid #00acc1;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 25px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/icons/arrow_down_dark.png); \n"
"    width: 14px;\n"
"    height: 14px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #ffffff;\n"
"    color: #004d40;\n"
"    border: 1px solid #4dd0e1;\n"
"    selection-background-color: #b2dfdb;\n"
"    font: 11pt \"Segoe UI\";\n"
"}\n"
""));
        turn_box->setEditable(false);
        groupBox_p_2 = new QGroupBox(centralwidget);
        groupBox_p_2->setObjectName("groupBox_p_2");
        groupBox_p_2->setGeometry(QRect(0, 0, 201, 111));
        groupBox_p_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: none;\n"
"}\n"
""));
        groupBox_p_2->setFlat(false);
        groupBox_p_2->setCheckable(false);
        groupBox_p_2->setChecked(false);
        Turnpage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Turnpage);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 391, 25));
        Turnpage->setMenuBar(menubar);
        statusbar = new QStatusBar(Turnpage);
        statusbar->setObjectName("statusbar");
        Turnpage->setStatusBar(statusbar);

        retranslateUi(Turnpage);

        QMetaObject::connectSlotsByName(Turnpage);
    } // setupUi

    void retranslateUi(QMainWindow *Turnpage)
    {
        Turnpage->setWindowTitle(QCoreApplication::translate("Turnpage", "MainWindow", nullptr));
        groupBox_p->setTitle(QString());
        start_game->setText(QCoreApplication::translate("Turnpage", "Start Game", nullptr));
        back_tomain_p->setText(QCoreApplication::translate("Turnpage", "Main Menu", nullptr));
        turn_label->setText(QCoreApplication::translate("Turnpage", "Player 1 Turn", nullptr));
        turn_box->setCurrentText(QString());
        turn_box->setPlaceholderText(QCoreApplication::translate("Turnpage", "      \342\235\214 or \342\255\225", nullptr));
        groupBox_p_2->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class Turnpage: public Ui_Turnpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURNPAGE_H
