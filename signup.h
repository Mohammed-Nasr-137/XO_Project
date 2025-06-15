#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QWidget>
#include <QDebug>

namespace Ui {
class Signup;
}

class Signup : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_reg_button_clicked();

    void on_back_button_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
