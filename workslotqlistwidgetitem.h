#ifndef WORKSLOTQLISTWIDGETITEM_H
#define WORKSLOTQLISTWIDGETITEM_H

#include <QListWidgetItem>

#include "workslot.h"

class WorkSlotQListWidgetItem : public QListWidgetItem
{
public:
    WorkSlotQListWidgetItem(WorkSlot *Slot);

    bool operator<(const QListWidgetItem &other) const override;

private:

    WorkSlot *slot;

};

#endif // WORKSLOTQLISTWIDGETITEM_H
