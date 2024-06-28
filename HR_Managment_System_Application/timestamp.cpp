#include "timestamp.h"


Timestamp::Timestamp(QObject *parent, QDateTime start, QDateTime ende)
    :QObject{parent}
{
    this->data.first = start;
    this->data.second = ende;
}
