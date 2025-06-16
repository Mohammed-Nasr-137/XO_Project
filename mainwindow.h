#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_exitgame_button_clicked();
    void saveUsernameIfChecked();
    void loadSavedUsernames();
    void on_login_button_clicked();

    void on_savedusers_currentTextChanged(const QString &arg1);

    void on_signup_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
