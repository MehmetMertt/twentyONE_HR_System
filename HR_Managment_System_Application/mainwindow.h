#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


#include <nav/navbar.h>
#include <nav/navbar_compact.h>
#include <auth/login.h>
#include <auth/signup.h>
#include <auth/account.h>
#include <auth/account_adminview.h>

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
    void on_close_nav_button_clicked();

    void on_open_nav_button_clicked();

private:
    Ui::MainWindow *ui;
    Navbar* navbar;
    Navbar_compact* navbar_comp;
    Login* login_page;
    Signup* signup_page;
    Account* account_page;
    Account_adminview* account_adminview_page;
    QRect navbar_comp_geometry;
    QRect navbar_comp_closed_geometry;
    QRect navbar_geometry;
    QRect navbar_closed_geometry;
};
#endif // MAINWINDOW_H
