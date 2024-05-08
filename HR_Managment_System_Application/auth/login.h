#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "inputvalidator.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    InputValidator *validator;

private slots:
    void onEmailInputChanged();
    void onPasswordInputChanged();
    void on_button_clicked();
};

#endif // LOGIN_H
