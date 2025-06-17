#ifndef TURNPAGE_H
#define TURNPAGE_H
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QMainWindow>
namespace Ui {
class Turnpage;
}

class Turnpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Turnpage(QWidget *parent = nullptr);
    ~Turnpage();

private slots:
    void on_back_tomain_p_clicked();

    void on_turn_box_currentTextChanged(const QString &arg1);

    void on_turn_box_activated(int index);

    void on_start_game_clicked();

private:
    Ui::Turnpage *ui;
};

#endif // TURNPAGE_H
