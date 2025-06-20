#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <QMainWindow>
#include <qlistwidget.h>
#include <qpushbutton.h>

namespace Ui {
class Gamehistory;
}

class Gamehistory : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gamehistory(QWidget *parent = nullptr);
    ~Gamehistory();

private slots:

    void on_back_button_clicked();

private:
    Ui::Gamehistory *ui;

    void filterHistory(const QString &query);
    void onHistoryItemClicked(QListWidgetItem* item);
    QPushButton* determine_button(int position);
};

#endif // GAMEHISTORY_H
