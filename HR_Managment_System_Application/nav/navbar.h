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

private:
    Ui::Navbar *ui;
};

#endif // NAVBAR_H
