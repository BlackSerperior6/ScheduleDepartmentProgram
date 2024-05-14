#ifndef PARSEDWORKSLOT_H
#define PARSEDWORKSLOT_H

#include <QString>
#include <QStringList>

struct ParsedWorkSlot
{
    ParsedWorkSlot(QString day, QString time, QString week) //Класс рабочего слота, переведенного в индексы
    {
        QStringList buffer;

        buffer << "Понедельник" << "Вторник" << "Среда" << "Четверг" << "Пятница" << "Суббота";
        DayIndex = buffer.indexOf(day);

        buffer.clear();

        buffer << "8:00" << "9:40" << "11:30" << "13:20" << "15:00" << "16:40";
        TimeIndex = buffer.indexOf(time);

        buffer.clear();

        buffer << "1" << "2";
        WeekIndex = buffer.indexOf(week);
    }

    bool operator==(ParsedWorkSlot &other) //Оператор присваивания
    {
        return DayIndex == other.DayIndex && TimeIndex == other.TimeIndex && WeekIndex == other.WeekIndex;
    }

    int DayIndex;
    int TimeIndex;
    int WeekIndex;
};

#endif // PARSEDWORKSLOT_H
