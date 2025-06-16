#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QMainWindow>

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

private slots:
    void on_Logout_button_clicked();

    void on_Player_button_clicked();

    void on_playAi_button_clicked();

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
