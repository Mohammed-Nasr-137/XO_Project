#ifndef STATE_H
#define STATE_H

#include <QMainWindow>

namespace Ui {
class State;
}

class State : public QMainWindow
{
    Q_OBJECT

public:
    explicit State(QWidget *parent = nullptr);
    ~State();

private slots:
    void on_playagain_clicked();

    void on_MainMenust_clicked();

private:
    Ui::State *ui;
};

#endif // STATE_H
