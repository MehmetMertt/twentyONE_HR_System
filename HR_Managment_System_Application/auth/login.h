#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "inputvalidator.h"
#include <dbmanager.h>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void login_success();

private slots:
    void on_login_button_clicked();

private:
    Ui::Login *ui;
    InputValidator *validator;

private slots:
    void onEmailInputChanged();
    void onPasswordInputChanged();
    void on_button_clicked();
    dbmanager* db;
};

#endif // LOGIN_H
