#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include "inputvalidator.h"
#pragma once

namespace Ui {
class Account;
}

class Account : public QWidget
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();

private:
    Ui::Account *ui;
    InputValidator *validator;

private slots:
    void onPasswortInputChanged();
    void onPasswort2InputChanged();
    void on_button_clicked();
};

#endif // ACCOUNT_H
