#ifndef ACCOUNT_ADMINVIEW_H
#define ACCOUNT_ADMINVIEW_H

#include <QWidget>

namespace Ui {
class Account_adminview;
}

class Account_adminview : public QWidget
{
    Q_OBJECT

public:
    explicit Account_adminview(QWidget *parent = nullptr);
    ~Account_adminview();

private:
    Ui::Account_adminview *ui;
};

#endif // ACCOUNT_ADMINVIEW_H
