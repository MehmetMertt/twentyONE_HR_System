#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <QWidget>

namespace Ui {
class Timetracker;
}

class Timetracker : public QWidget
{
    Q_OBJECT

public:
    explicit Timetracker(QWidget *parent = nullptr);
    ~Timetracker();

private:
    Ui::Timetracker *ui;
};

#endif // TIMETRACKER_H
