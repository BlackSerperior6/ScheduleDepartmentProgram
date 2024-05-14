#ifndef WORKSLOTQLISTWIDGETITEM_H
#define WORKSLOTQLISTWIDGETITEM_H

#include <QListWidgetItem>

#include "workslot.h"

class WorkSlotQListWidgetItem : public QListWidgetItem //Класс элемента списка рабочих слотов
{
public:
    WorkSlotQListWidgetItem(WorkSlot *Slot);

    bool operator<(const QListWidgetItem &other) const override;

private:

    WorkSlot *slot; //Привязанный слот

};

#endif // WORKSLOTQLISTWIDGETITEM_H
