#ifndef GAMEREPLAY_H
#define GAMEREPLAY_H

#include <QMainWindow>
#include <qpushbutton.h>


namespace Ui {
class Gamereplay;
}

class Gamereplay : public QMainWindow
{
    Q_OBJECT;
    QString x_p;
    QString o_p;
    QString winner_p;

public:
    explicit Gamereplay(QWidget *parent = nullptr);
    ~Gamereplay();

private slots:


    void on_nextButton_clicked();
    QPushButton* determine_button(int position);

    void on_prevButton_clicked();
    void update_icon(QPushButton* c);

    void on_back_button_clicked();

private:
    Ui::Gamereplay *ui;
};

#endif // GAMEREPLAY_H
