#include "changeteacherfrom.h"
#include "ui_changeteacherfrom.h"

#include <QMessageBox>

#include "workslotqlistwidgetitem.h"

ChangeTeacherFrom::ChangeTeacherFrom(QWidget *parent, Teacher *teacher, QListWidget *parentList) :
    QDialog(parent),
    ui(new Ui::ChangeTeacherFrom) //Форма редактирования учителя
{
    ui->setupUi(this);

    WorkSlotsRowSelected = -1;

    ParentList = parentList; //Предает список, из которого перешел учитель

    Teach = teacher; //Передаем учителя

    ui->NameEdit->setText(Teach->GetName()); //Передаем его имя в элемент ui

    QListWidget *list = Teach->GetWorkSlots();

    //Передаем его рабочие слоты в буфферный список
    for (int i = 0; i < list->count(); i++)
    {
        WorkSlot *slot = new WorkSlot(nullptr, false);
        WorkSlotQListWidgetItem *item = new WorkSlotQListWidgetItem(slot);

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
    if (ui->NameEdit->text().isEmpty()) //Сообщаем о ошибке, если нет именни
    {
        QMessageBox::information(nullptr, "Ошибка!", "Не указано ФИО преподователя!");
        return;
    }

    if (ui->WorkSlotsList->count() == 0) //Сообщаем о ошибке, если нет времени
    {
        QMessageBox::information(nullptr, "Ошибка!", "У преподователя должно быть рабочие время!");
        return;
    }

    bool flag = false;

    //Проверка, что учителя с таким именнем уже нет
    for (int i = 0; i < ParentList->count() && !flag; i++)
    {
        Teacher *current = (Teacher*) ParentList->itemWidget(ParentList->item(i));

        flag = Teach != current &&
                current->GetName() == ui->NameEdit->text();
    }

    //Сообщение о ошибке, если есть
    if (flag)
    {
        QMessageBox::information(nullptr, "Ошибка!", "Педагог с таким именем уже существует");
        return;
    }

    //Задамем имя учителя
    Teach->SetName(ui->NameEdit->text());

    QListWidget *list = Teach->GetWorkSlots();

    list->clear();

    //Переносим рабочие слоты из буффера в реальный список
    for (int i = 0; i < ui->WorkSlotsList->count(); i++)
    {
        WorkSlot *slot = new WorkSlot(nullptr, false);
        WorkSlotQListWidgetItem *item = new WorkSlotQListWidgetItem(slot);

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
    //Получаем редактируемый слот
    WorkSlot *slot = (WorkSlot*) ui->WorkSlotsList->itemWidget(item);

    //Вызываем ui для редактирования данных рабочего слота
    ChangeWorkSlot *win = new ChangeWorkSlot(nullptr, slot, ui->WorkSlotsList);

    win->setModal(true);
    win->exec();
}

void ChangeTeacherFrom::on_AddButton_clicked()
{
    //При добавлении нового рабочего слота вызываем контсруктор
    WorkSlot *slot = new WorkSlot(nullptr, true, ui->WorkSlotsList);
    WorkSlotQListWidgetItem *item = new WorkSlotQListWidgetItem(slot);

    //Если создание отменили
    if (!slot->IsSet())
    {
        //Чистим память
        delete slot;
        delete item;
        return;
    }

    //Добавляем в список и сортируем
    ui->WorkSlotsList->addItem(item);
    ui->WorkSlotsList->setItemWidget(item, slot);
    ui->WorkSlotsList->sortItems();
}

void ChangeTeacherFrom::on_WorkSlotsList_currentRowChanged(int currentRow)
{
    WorkSlotsRowSelected = currentRow;
}

void ChangeTeacherFrom::on_RemoveButton_clicked()
{
    if (WorkSlotsRowSelected == -1)
        return;

    //Удаляем выбранный элемент
    QListWidgetItem *it = ui->WorkSlotsList->takeItem(WorkSlotsRowSelected);
    delete it;

    ui->WorkSlotsList->setCurrentRow(-1);
}


void ChangeTeacherFrom::on_ClearButton_clicked()
{
    ui->WorkSlotsList->clear();
}
