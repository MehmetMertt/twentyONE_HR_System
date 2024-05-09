#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QtCharts/QLineSeries>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
