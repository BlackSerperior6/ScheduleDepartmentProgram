#ifndef WORKSLOT_H
#define WORKSLOT_H

#include <QWidget>
#include <QLabel>

#include <QListWidget>

class WorkSlot : public QWidget
{
    Q_OBJECT
public:
    explicit WorkSlot(QWidget *parent = nullptr, bool shouldCallDialogs = true, QListWidget *parentList = nullptr);

    QString GetDay();

    QString GetTime();

    QString GetWhatWeek();

    bool IsSet();

    void ChangeIsSet(bool set);

    void SetDay(QString day);

    void SetTime(QString time);

    void SetWhatWeek(QString week);

    void operator=(WorkSlot &slot);

    bool operator==(WorkSlot &slot);

    bool operator!=(WorkSlot &slot);

    bool Compare(QString day, QString time, QString whatWeek);

private:
    QLabel *Day;
    QLabel *Time;
    QLabel *WhatWeek;

    bool isSet;



signals:

};

#endif // WORKSLOT_H
