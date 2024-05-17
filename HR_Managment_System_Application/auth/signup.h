#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include "inputvalidator.h"

namespace Ui {
class Signup;
}

class Signup : public QWidget
{
    Q_OBJECT

public:
    Signup(QWidget *parent = nullptr);
    ~Signup();

signals:
    void signup_success();

private:
    Ui::Signup *ui;
    InputValidator *validator;


private slots:
    void on_button_clicked();
    void onVornameInputChanged();
    void onNachnameInputChanged();
    void onEmailInputChanged();
    void onTelefonInputChanged();
    void onAdresseInputChanged();
    void onPlzInputChanged();
    void onOrtInputChanged();
    void onPasswordInputChanged();
};

#endif // SIGNUP_H
