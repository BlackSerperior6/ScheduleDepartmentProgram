#include "workslot.h"

#include "changeworkslot.h"

WorkSlot::WorkSlot(QWidget *parent, bool shouldCallDialogs,
                   QListWidget *parentList) : QWidget(parent)
{
    Day = new QLabel(this);
    Day->setGeometry(10, 0, 81, 16);

    Time = new QLabel(this);
    Time->setGeometry(100, 0, 31, 16);

    WhatWeek = new QLabel(this);
    WhatWeek->setGeometry(150, 0, 21, 16);

    isSet = false;

    if (shouldCallDialogs)
    {
        ChangeWorkSlot *win = new ChangeWorkSlot(nullptr, this, parentList);

        win->setModal(true);
        win->exec();
    }
}

QString WorkSlot::GetDay()
{
    return Day->text();
}

QString WorkSlot::GetTime()
{
    return Time->text();
}

QString WorkSlot::GetWhatWeek()
{
    return WhatWeek->text();
}

void WorkSlot::SetDay(QString day)
{
    Day->setText(day);
}

void WorkSlot::SetTime(QString time)
{
    Time->setText(time);
}

void WorkSlot::SetWhatWeek(QString week)
{
    WhatWeek->setText(week);
}

void WorkSlot::operator=(WorkSlot &slot)
{
    SetDay(slot.GetDay());
    SetTime(slot.GetTime());
    SetWhatWeek(slot.GetWhatWeek());
}

bool WorkSlot::Compare(QString day, QString time, QString whatWeek)
{
    return GetDay() == day && GetTime() == time && GetWhatWeek() == whatWeek;
}

bool WorkSlot::IsSet()
{
    return isSet;
}

void WorkSlot::ChangeIsSet(bool set)
{
    isSet = set;
}

ParsedWorkSlot WorkSlot::ParseToIndexes()
{
    return ParsedWorkSlot(Day->text(), Time->text(), WhatWeek->text());
}
