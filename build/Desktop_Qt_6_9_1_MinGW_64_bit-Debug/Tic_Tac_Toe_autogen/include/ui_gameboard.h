/********************************************************************************
** Form generated from reading UI file 'gameboard.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARD_H
#define UI_GAMEBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gameboard
{
public:
    QWidget *centralwidget;
    QPushButton *Reset_button;
    QPushButton *Back_gboard;
    QWidget *gridLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *p1_label;
    QLabel *another_label;
    QPushButton *c_1;
    QPushButton *c_3;
    QPushButton *c_2;
    QPushButton *c_6;
    QPushButton *c_5;
    QPushButton *c_4;
    QPushButton *c_9;
    QPushButton *c_8;
    QPushButton *c_7;
    QLabel *upper;
    QLabel *Lower;
    QLabel *Right;
    QLabel *left;
    QPushButton *undo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Gameboard)
    {
        if (Gameboard->objectName().isEmpty())
            Gameboard->setObjectName("Gameboard");
        Gameboard->resize(521, 627);
        Gameboard->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background: qlineargradient(\n"
"        spread: pad,\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(0, 34, 133, 180),\n"
"        stop: 1 rgba(255, 255, 255, 80)\n"
"    );\n"
"}\n"
""));
        centralwidget = new QWidget(Gameboard);
        centralwidget->setObjectName("centralwidget");
        Reset_button = new QPushButton(centralwidget);
        Reset_button->setObjectName("Reset_button");
        Reset_button->setGeometry(QRect(10, 550, 151, 51));
        Reset_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        Back_gboard = new QPushButton(centralwidget);
        Back_gboard->setObjectName("Back_gboard");
        Back_gboard->setGeometry(QRect(360, 550, 151, 51));
        Back_gboard->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(-20, 0, 561, 65));
        horizontalLayout = new QHBoxLayout(gridLayoutWidget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        p1_label = new QLabel(gridLayoutWidget_2);
        p1_label->setObjectName("p1_label");
        p1_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: qlineargradient(\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(30, 60, 114, 150),  \n"
"        stop: 1 rgba(42, 82, 152, 150)   \n"
"    );\n"
"    color: white;\n"
"    font: bold 14pt \"Segoe UI\";\n"
"    padding: 14px;\n"
"    border-radius: 20px;\n"
"    border: 2px solid rgba(255, 255, 255, 180); \n"
"    qproperty-alignment: AlignCenter;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    background-color: qlineargradient(\n"
"        x1: 1, y1: 0,\n"
"        x2: 0, y2: 1,\n"
"        stop: 0 rgba(58, 28, 113, 180),  \n"
"        stop: 1 rgba(215, 109, 119, 180)  \n"
"    );\n"
"    color: #FFEB3B;\n"
"    border: 2px solid #FFEB3B;\n"
"}\n"
""));

        horizontalLayout->addWidget(p1_label);

        another_label = new QLabel(gridLayoutWidget_2);
        another_label->setObjectName("another_label");
        another_label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: qlineargradient(\n"
"        x1: 0, y1: 0,\n"
"        x2: 1, y2: 1,\n"
"        stop: 0 rgba(30, 60, 114, 150),   /* Dark Blue with transparency */\n"
"        stop: 1 rgba(42, 82, 152, 150)    /* Medium Blue with transparency */\n"
"    );\n"
"    color: white;\n"
"    font: bold 14pt \"Segoe UI\";\n"
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

        horizontalLayout->addWidget(another_label);

        c_1 = new QPushButton(centralwidget);
        c_1->setObjectName("c_1");
        c_1->setGeometry(QRect(40, 80, 141, 151));
        QFont font;
        font.setPointSize(36);
        c_1->setFont(font);
        c_1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Downloads/Adobe Express - file.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        c_1->setIcon(icon);
        c_1->setIconSize(QSize(150, 125));
        c_3 = new QPushButton(centralwidget);
        c_3->setObjectName("c_3");
        c_3->setGeometry(QRect(340, 80, 141, 151));
        c_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_3->setIcon(icon);
        c_3->setIconSize(QSize(150, 125));
        c_2 = new QPushButton(centralwidget);
        c_2->setObjectName("c_2");
        c_2->setGeometry(QRect(180, 80, 161, 151));
        c_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../Downloads/Adobe Express - file (1).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        c_2->setIcon(icon1);
        c_2->setIconSize(QSize(150, 120));
        c_6 = new QPushButton(centralwidget);
        c_6->setObjectName("c_6");
        c_6->setGeometry(QRect(340, 230, 141, 151));
        c_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_6->setIcon(icon1);
        c_6->setIconSize(QSize(150, 125));
        c_5 = new QPushButton(centralwidget);
        c_5->setObjectName("c_5");
        c_5->setGeometry(QRect(180, 230, 161, 151));
        c_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_5->setIcon(icon);
        c_5->setIconSize(QSize(150, 120));
        c_4 = new QPushButton(centralwidget);
        c_4->setObjectName("c_4");
        c_4->setGeometry(QRect(40, 230, 141, 151));
        c_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_4->setIcon(icon1);
        c_4->setIconSize(QSize(150, 125));
        c_9 = new QPushButton(centralwidget);
        c_9->setObjectName("c_9");
        c_9->setGeometry(QRect(340, 380, 141, 141));
        c_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_9->setIcon(icon);
        c_9->setIconSize(QSize(150, 125));
        c_8 = new QPushButton(centralwidget);
        c_8->setObjectName("c_8");
        c_8->setGeometry(QRect(180, 380, 161, 141));
        c_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_8->setIcon(icon);
        c_8->setIconSize(QSize(150, 120));
        c_7 = new QPushButton(centralwidget);
        c_7->setObjectName("c_7");
        c_7->setGeometry(QRect(40, 380, 141, 141));
        c_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}"));
        c_7->setIcon(icon1);
        c_7->setIconSize(QSize(150, 125));
        upper = new QLabel(centralwidget);
        upper->setObjectName("upper");
        upper->setGeometry(QRect(40, 220, 441, 16));
        QFont font1;
        font1.setWeight(QFont::Thin);
        upper->setFont(font1);
        upper->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: rgba(255, 255, 255, 0.5); /* Neon white with 30% opacity */\n"
"    border: none;\n"
"    min-width: 0px;\n"
"    min-height: 0px;\n"
"    border-radius: 7px;\n"
"    box-shadow: 0 0 4px rgba(255, 255, 255, 0.5); /* Lighter neon glow */\n"
"}"));
        Lower = new QLabel(centralwidget);
        Lower->setObjectName("Lower");
        Lower->setGeometry(QRect(40, 370, 441, 20));
        Lower->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: rgba(255, 255, 255, 0.5); /* Neon white with 30% opacity */\n"
"    border: none;\n"
"    min-width: 0px;\n"
"    min-height: 0px;\n"
"    border-radius: 7px;\n"
"    box-shadow: 0 0 4px rgba(255, 255, 255, 0.5); /* Lighter neon glow */\n"
"}"));
        Right = new QLabel(centralwidget);
        Right->setObjectName("Right");
        Right->setGeometry(QRect(171, 79, 16, 441));
        Right->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    background-color: rgba(255, 255, 255, 0.7); /* Neon white with 30% opacity */\n"
"    border: none;\n"
"    min-width: 0px;\n"
"    min-height: 0px;\n"
"    border-radius: 7px;\n"
"    box-shadow: 0 0 4px rgba(255, 255, 255, 0.7); /* Lighter neon glow */\n"
"}"));
        left = new QLabel(centralwidget);
        left->setObjectName("left");
        left->setGeometry(QRect(331, 80, 16, 441));
        left->setStyleSheet(QString::fromUtf8("QLabel#left {\n"
"    background-color: rgba(255, 255, 255, 0.7); /* Neon white with 30% opacity */\n"
"    border: none;\n"
"    min-width: 0px;\n"
"    min-height: 0px;\n"
"    border-radius: 7px;\n"
"    box-shadow: 0 0 4px rgba(255, 255, 255, 0.7); /* Lighter neon glow */\n"
"}"));
        left->setLineWidth(0);
        undo = new QPushButton(centralwidget);
        undo->setObjectName("undo");
        undo->setGeometry(QRect(190, 550, 141, 51));
        undo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        Gameboard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Gameboard);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 521, 25));
        Gameboard->setMenuBar(menubar);
        statusbar = new QStatusBar(Gameboard);
        statusbar->setObjectName("statusbar");
        Gameboard->setStatusBar(statusbar);

        retranslateUi(Gameboard);

        QMetaObject::connectSlotsByName(Gameboard);
    } // setupUi

    void retranslateUi(QMainWindow *Gameboard)
    {
        Gameboard->setWindowTitle(QCoreApplication::translate("Gameboard", "MainWindow", nullptr));
        Reset_button->setText(QCoreApplication::translate("Gameboard", "Reset", nullptr));
        Back_gboard->setText(QCoreApplication::translate("Gameboard", "Main Menu", nullptr));
        p1_label->setText(QCoreApplication::translate("Gameboard", "TextLabel", nullptr));
        another_label->setText(QCoreApplication::translate("Gameboard", "TextLabel", nullptr));
        c_1->setText(QString());
        c_3->setText(QString());
        c_2->setText(QString());
        c_6->setText(QString());
        c_5->setText(QString());
        c_4->setText(QString());
        c_9->setText(QString());
        c_8->setText(QString());
        c_7->setText(QString());
        upper->setText(QString());
        Lower->setText(QString());
        Right->setText(QString());
        left->setText(QString());
        undo->setText(QCoreApplication::translate("Gameboard", "Undo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gameboard: public Ui_Gameboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARD_H
