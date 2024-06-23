#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


#include <nav/navbar.h>
#include <nav/navbar_compact.h>
#include <auth/login.h>
#include <auth/signup.h>
#include <auth/account.h>
#include <auth/account_adminview.h>
#include <mainloading.h>
#include <dashboard.h>
#include <admindashboard.h>
#include <dbmanager.h>
#include <timetracker.h>
#include <requests.h>
#include <settings.h>
#include <editzeiteintrag.h>
#include <Helpers.h>
#include <antrag_detailpage.h>
//---------------------------
#pragma once
#include <dbaccess.h>
#include <QFile>
#include <QPropertyAnimation>
#include <QtSql/QSqlDatabase>
#include <QDebug>
//---------------------------
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
    void login_finished();

private slots:
    void on_close_nav_button_clicked();

    void on_open_nav_button_clicked();





private:
    Ui::MainWindow *ui;
    MainLoading* main_loading_page = nullptr;
    Navbar* navbar= nullptr;
    Navbar_compact* navbar_comp= nullptr;

    Login* login_page= nullptr;
    Signup* signup_page= nullptr;
    Account* account_page= nullptr;
    Account_adminview* account_adminview_page= nullptr;
    AdminDashboard* admin_dashboard= nullptr;
    Dashboard* dashboard= nullptr;
    Timetracker* timetracker_page= nullptr;
    Requests* request_page= nullptr;
    Settings* settings_page= nullptr;
    EditZeiteintrag* editZeiteintrag_page= nullptr;
    AntragDetails* antrag_detail_page= nullptr;

    QRect navbar_comp_geometry;
    QRect navbar_comp_closed_geometry;
    QRect navbar_geometry;
    QRect navbar_closed_geometry;

    void onLoadingFinished();
    void showAccount();
    void showDashboard();
    void showTimetracker(Mode mode);
    void showRequests(Mode mode = LOAD_DATA);
    void showAntragDetailPage(Mode mode, Mode page, Antrag* antrag = nullptr);
    void showSettings();
    void processLogout();
    void showAdminDashboard();
    void showSignup();
    void openEditEmployeeView(int id);
    void openEditZeiteintragView(QList<Timestamp*> timestamps);
    void loadEmployeesThenShowAdminDashboard();

    void startZeitaufzeichnungFromDashboard();
};
#endif // MAINWINDOW_H
