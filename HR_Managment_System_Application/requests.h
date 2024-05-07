#ifndef REQUESTS_H
#define REQUESTS_H

#include <QWidget>

namespace Ui {
class Requests;
}

class Requests : public QWidget
{
    Q_OBJECT

public:
    explicit Requests(QWidget *parent = nullptr);
    ~Requests();

private:
    Ui::Requests *ui;
};

#endif // REQUESTS_H
