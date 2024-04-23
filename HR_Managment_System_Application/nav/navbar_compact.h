#ifndef NAVBAR_COMPACT_H
#define NAVBAR_COMPACT_H

#include <QWidget>

namespace Ui {
class Navbar_compact;
}

class Navbar_compact : public QWidget
{
    Q_OBJECT

public:
    explicit Navbar_compact(QWidget *parent = nullptr);
    ~Navbar_compact();

private:
    Ui::Navbar_compact *ui;
};

#endif // NAVBAR_COMPACT_H
