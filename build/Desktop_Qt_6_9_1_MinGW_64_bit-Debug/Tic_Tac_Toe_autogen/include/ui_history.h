/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_History
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *History)
    {
        if (History->objectName().isEmpty())
            History->setObjectName("History");
        History->resize(800, 600);
        centralwidget = new QWidget(History);
        centralwidget->setObjectName("centralwidget");
        History->setCentralWidget(centralwidget);
        menubar = new QMenuBar(History);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        History->setMenuBar(menubar);
        statusbar = new QStatusBar(History);
        statusbar->setObjectName("statusbar");
        History->setStatusBar(statusbar);

        retranslateUi(History);

        QMetaObject::connectSlotsByName(History);
    } // setupUi

    void retranslateUi(QMainWindow *History)
    {
        History->setWindowTitle(QCoreApplication::translate("History", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class History: public Ui_History {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
