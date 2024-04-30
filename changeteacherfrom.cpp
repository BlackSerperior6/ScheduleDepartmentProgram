#include "changeteacherfrom.h"
#include "ui_changeteacherfrom.h"
#include <QMessageBox>

ChangeTeacherFrom::ChangeTeacherFrom(QWidget *parent, Teacher *teacher, QListWidget *parentList) :
    QDialog(parent),
    ui(new Ui::ChangeTeacherFrom)
{
    ui->setupUi(this);

    WorkSlotsRowSelected = -1;

    ParentList = parentList;

    Teach = teacher;

    ui->NameEdit->setText(Teach->GetName());

    QListWidget *list = Teach->GetWorkSlots();

    for (int i = 0; i < list->count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;

        WorkSlot *slot = new WorkSlot(nullptr, false);

        *slot = *((WorkSlot*) list->itemWidget(list->item(i)));

        ui->WorkSlotsList->addItem(item);
        ui->WorkSlotsList->setItemWidget(item, slot);
    }
}

ChangeTeacherFrom::~ChangeTeacherFrom()
{
    delete ui;
}

void ChangeTeacherFrom::on_DialogButtons_accepted()
{
    bool flag = false;

    for (int i = 0; i < ParentList->count() && !flag; i++)
    {
        Teacher *current = (Teacher*) ParentList->itemWidget(ParentList->item(i));

        flag = Teach != current &&
                current->GetName() == ui->NameEdit->text();
    }

    if (flag)
    {
        QMessageBox::information(nullptr, "Ошибка!", "Учитель с таким именем уже существует");
        return;
    }

    Teach->SetName(ui->NameEdit->text());

    QListWidget *list = Teach->GetWorkSlots();

    list->clear();

    for (int i = 0; i < ui->WorkSlotsList->count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;

        WorkSlot *slot = new WorkSlot(nullptr, false);

        *slot = *((WorkSlot*) ui->WorkSlotsList->itemWidget(ui->WorkSlotsList->item(i)));

        list->addItem(item);
        list->setItemWidget(item, slot);
    }

    this->close();
}

void ChangeTeacherFrom::on_DialogButtons_rejected()
{
    this->close();
}

void ChangeTeacherFrom::on_WorkSlotsList_itemDoubleClicked(QListWidgetItem *item)
{
    WorkSlot *slot = (WorkSlot*) ui->WorkSlotsList->itemWidget(item);

    ChangeWorkSlot *win = new ChangeWorkSlot(nullptr, slot, ui->WorkSlotsList);

    win->setModal(true);
    win->exec();
}

void ChangeTeacherFrom::on_AddButton_clicked()
{
    QListWidgetItem *item = new QListWidgetItem;
    WorkSlot *slot = new WorkSlot(nullptr, true, ui->WorkSlotsList);

    if (!slot->IsSet())
    {
        delete slot;
        delete item;
        return;
    }

    ui->WorkSlotsList->addItem(item);
    ui->WorkSlotsList->setItemWidget(item, slot);
}

void ChangeTeacherFrom::on_WorkSlotsList_currentRowChanged(int currentRow)
{
    WorkSlotsRowSelected = currentRow;
}

void ChangeTeacherFrom::on_RemoveButton_clicked()
{
    if (WorkSlotsRowSelected == -1)
        return;

    QListWidgetItem *it = ui->WorkSlotsList->takeItem(WorkSlotsRowSelected);
    delete it;

    ui->WorkSlotsList->setCurrentRow(-1);
}

