#ifndef REQUESTS_H
#define REQUESTS_H

#include <QWidget>
#include <Helpers.h>
#include "antrag_listitem.h"
#include <antrag.h>
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

    void updateView(Mode mode);

signals:
    void showAntragDetailPage(Mode mode, Mode page, Antrag* antrag);

private slots:

    void on_new_antrag_button_clicked();

private:
    Ui::Requests *ui;

    void processAntragDetailClicked(Antrag* antrag);

    void insertRequests();

    QList<AntragListItem*> antrag_list_items;

};

#endif // REQUESTS_H
