#ifndef WORKSLOT_H
#define WORKSLOT_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>

#include "ParsedWorkSlot.h"

class WorkSlot : public QWidget //Класс рабочего слота
{
    Q_OBJECT
public:
    explicit WorkSlot(QWidget *parent = nullptr, bool shouldCallDialogs = true,
                      QListWidget *parentList = nullptr);

    QString GetDay();

    QString GetTime();

    QString GetWhatWeek();

    bool IsSet();

    void ChangeIsSet(bool set);

    void SetDay(QString day);

    void SetTime(QString time);

    void SetWhatWeek(QString week);

    void operator=(WorkSlot &slot);

    bool Compare(QString day, QString time, QString whatWeek);

    ParsedWorkSlot ParseToIndexes();

private:
    QLabel *Day; //День
    QLabel *Time; //Время
    QLabel *WhatWeek; //Номер недели

    bool isSet;

signals:

};

#endif // WORKSLOT_H
