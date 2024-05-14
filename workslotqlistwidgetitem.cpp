#include "workslotqlistwidgetitem.h"
#include "workslot.h"

#include "ParsedWorkSlot.h"

WorkSlotQListWidgetItem::WorkSlotQListWidgetItem(WorkSlot * Slot) //Элемент списка рабочих слотов
{
    slot = Slot;
}

bool WorkSlotQListWidgetItem::operator<(const QListWidgetItem &other) const //Перегруженный оператор <
{
    ParsedWorkSlot main = (slot)->ParseToIndexes();
    ParsedWorkSlot toCompare = (static_cast<const WorkSlotQListWidgetItem&>(other)).slot->ParseToIndexes();

    //Пытаемся сравнить по дням
    if (main.DayIndex != toCompare.DayIndex)
        return main.DayIndex < toCompare.DayIndex;

    //Потом по времени
    if (main.TimeIndex != toCompare.TimeIndex)
        return main.TimeIndex < toCompare.TimeIndex;

    //Наконец по номеру недели
    return main.WeekIndex < toCompare.WeekIndex;
}
