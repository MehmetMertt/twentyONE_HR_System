#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#pragma once

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    void logout();

signals:
    void logout_success();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
