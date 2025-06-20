#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QMainWindow>

namespace Ui {
class Gameboard;
}

class Gameboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gameboard(QWidget *parent = nullptr);
    ~Gameboard();

    // friend class State;

private slots:

    void get_head_to_head_stats();

    void on_Back_gboard_clicked();

    int make_ai_play();

    void update_label();

    void update_gui(QPushButton* c, int pos);

    void handleAiTurnDelayed();

    void make_human_play(QPushButton* c, int pos);

    void on_c_1_clicked();

    void on_c_2_clicked();

    void on_c_3_clicked();

    void on_c_4_clicked();

    void on_c_5_clicked();

    void on_c_6_clicked();

    void on_c_7_clicked();

    void on_c_8_clicked();

    void on_c_9_clicked();

    void on_Reset_button_clicked();

    void on_undo_clicked();

private:
    Ui::Gameboard *ui;
};

#endif // GAMEBOARD_H
