#ifndef NAVBAR_COMPACT_H
#define NAVBAR_COMPACT_H

#include <QWidget>
#pragma once

namespace Ui {
class Navbar_compact;
}

class Navbar_compact : public QWidget
{
    Q_OBJECT

public:
    explicit Navbar_compact(QWidget *parent = nullptr);
    ~Navbar_compact();

    QString getActiveItem();
    void setActiveItem(QString item);

signals:
    void account_clicked();
    void dashboard_clicked();
    void timetracker_clicked();
    void request_clicked();
    void settings_clicked();
    void logout_clicked();
    void admin_clicked();

private slots:
    void on_user_clicked();

    void on_dashboard_clicked();

    void on_timetracker_clicked();

    void on_request_clicked();

    void on_settings_clicked();

    void on_logout_button_clicked();

    void on_admin_button_clicked();

private:
    Ui::Navbar_compact *ui;

    QMap<QString, QWidget*> items;

    QWidget* active_item;

    void removeActiveItem();
    void addActiveItem();
};

#endif // NAVBAR_COMPACT_H
