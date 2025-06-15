#ifndef AIPAGE_H
#define AIPAGE_H
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QMainWindow>

namespace Ui {
class Aipage;
}

class Aipage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Aipage(QWidget *parent = nullptr);
    ~Aipage();

private slots:
    void on_level_ai_currentTextChanged(const QString &arg1);

    void on_turn_box_ai_currentTextChanged(const QString &arg1);

    void on_back_tomain_ai_clicked();

    void on_level_ai_currentIndexChanged(int index);

private:
    Ui::Aipage *ui;
};

#endif // AIPAGE_H
