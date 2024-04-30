#include "teacher.h"
#include "changeteacherfrom.h"

Teacher::Teacher(QWidget *parent, QListWidget *parentList) : QWidget(parent)
{
    Name = new QLabel(this);
    Name->setGeometry(10, 0, 191, 20);

    WorkSlots = new QListWidget;

    ChangeTeacherFrom *win = new ChangeTeacherFrom(nullptr, this, parentList);

    win->setModal(true);
    win->exec();
}

QListWidget* Teacher::GetWorkSlots()
{
    return WorkSlots;
}

QString Teacher::GetName()
{
    return Name->text();
}

void Teacher::SetWorkSlots(QListWidget *list)
{
    WorkSlots->clear();

    for (int i = 0;i < list->count(); i++)
    {
        QListWidgetItem *item = list->item(i);

        WorkSlot *slot = (WorkSlot*) list->itemWidget(item);

        list->addItem(item);
        list->setItemWidget(item, slot);
    }
}

void Teacher::SetName(QString name)
{
    Name->setText(name);
}
