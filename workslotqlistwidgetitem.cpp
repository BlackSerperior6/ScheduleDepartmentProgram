#include "workslotqlistwidgetitem.h"
#include "workslot.h"
#include "ParsedWorkSlot.h"

WorkSlotQListWidgetItem::WorkSlotQListWidgetItem(WorkSlot * Slot)
{
    slot = Slot;
}

bool WorkSlotQListWidgetItem::operator<(const QListWidgetItem &other) const
{
    ParsedWorkSlot main = (slot)->ParseToIndexes();
    ParsedWorkSlot toCompare = (static_cast<const WorkSlotQListWidgetItem&>(other)).slot->ParseToIndexes();

    if (main.DayIndex != toCompare.DayIndex)
        return main.DayIndex < toCompare.DayIndex;

    if (main.TimeIndex != toCompare.TimeIndex)
        return main.TimeIndex < toCompare.TimeIndex;

    return main.WeekIndex < toCompare.WeekIndex;
}
