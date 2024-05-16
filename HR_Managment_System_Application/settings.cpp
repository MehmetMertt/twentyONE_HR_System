#include "settings.h"
#include "ui_settings.h"

#include <dbaccess.h>

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::logout() {

    delete currentEmployee;

    qDebug() << "curennt employee removed";
    emit logout_success();

}
