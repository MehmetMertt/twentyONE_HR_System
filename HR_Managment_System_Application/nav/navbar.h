#ifndef NAVBAR_H
#define NAVBAR_H

#include <QWidget>

namespace Ui {
class Navbar;
}

class Navbar : public QWidget
{
    Q_OBJECT

public:
    explicit Navbar(QWidget *parent = nullptr);
    ~Navbar();
    void setUserData();

    QString getActiveItem();
    void setActiveItem(QString item);

signals:
    void account_clicked();
    void dashboard_clicked();
    void timetracker_clicked();
    void request_clicked();
    void settings_clicked();
    void logout_clicked();

private slots:

    void on_user_clicked();

    void on_dashboard_clicked();

    void on_timetracker_clicked();

    void on_request_clicked();

    void on_logout_button_clicked();

    void on_settings_clicked();

private:
    Ui::Navbar *ui;

    QMap<QString, QWidget*> items;

    QWidget* active_item;

    void removeActiveItem();
    void addActiveItem();
};

#endif // NAVBAR_H
