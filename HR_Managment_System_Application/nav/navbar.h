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
    void processLoginOutButton(int logged);
    void setUserData();

signals:
    void account_clicked();
    void dashboard_clicked();

private slots:

    void on_user_clicked();

    void on_dashboard_clicked();

private:
    Ui::Navbar *ui;
};

#endif // NAVBAR_H
