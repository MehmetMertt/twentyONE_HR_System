#ifndef REQUESTS_H
#define REQUESTS_H

#include <QWidget>
#include <Helpers.h>
#pragma once

namespace Ui {
class Requests;
}

class Requests : public QWidget
{
    Q_OBJECT

public:
    explicit Requests(QWidget *parent = nullptr);
    ~Requests();

signals:
    void showAntragDetailPage(Mode mode);

private slots:

    void on_new_antrag_button_clicked();

private:
    Ui::Requests *ui;

    void processAntragDetailClicked();
};

#endif // REQUESTS_H
