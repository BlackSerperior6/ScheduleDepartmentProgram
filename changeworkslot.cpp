#include "changeworkslot.h"
#include "ui_changeworkslot.h"

#include <QMessageBox>

ChangeWorkSlot::ChangeWorkSlot(QWidget *parent, WorkSlot *slot, QListWidget *parentlist) :
    QDialog(parent),
    ui(new Ui::ChangeWorkSlot) //ui для редактирования рабочего слота учителя
{
    ui->setupUi(this);

    //Передаем слот и родительский список
    Slot = slot;
    Parentlist = parentlist;

    bool flag = false;

    //Задаем элементам ui элементы слота
    for (int i = 0; i < ui->DayBox->count() && !flag; i++ )
    {
        if (Slot->GetDay() == ui->DayBox->itemText(i))
        {
            flag = true;
            ui->DayBox->setCurrentIndex(i);
        }
    }

    flag = false;

    for (int i = 0; i < ui->TimeBox->count() && !flag; i++ )
    {
        if (Slot->GetTime() == ui->TimeBox->itemText(i))
        {
            flag = true;
            ui->TimeBox->setCurrentIndex(i);
        }
    }

    flag = false;

    for (int i = 0; i < ui->WeekBox->count() && !flag; i++ )
    {
        if (Slot->GetWhatWeek() == ui->WeekBox->itemText(i))
        {
            flag = true;
            ui->WeekBox->setCurrentIndex(i);
        }
    }
}

ChangeWorkSlot::~ChangeWorkSlot()
{
    delete ui;
}

void ChangeWorkSlot::on_DialogButtons_accepted()
{
    bool flag = false;

    //Проверка, что такого слота уже нет
    for (int i = 0; i < Parentlist->count() && !flag; i++)
    {
        WorkSlot *current = (WorkSlot*)
                Parentlist->itemWidget(
                    Parentlist->item(i));

        flag = Slot != current && current->Compare(ui->DayBox->currentText(),
                                ui->TimeBox->currentText(),
                                ui->WeekBox->currentText());
    }

    //Если есть, выдаем сообщение о ошибке
    if (flag)
    {
        QMessageBox::information(nullptr, "Ошибка!",
                                 "Такой элемент уже есть в списке");
        return;
    }

    flag = !Slot->GetDay().isEmpty();

    //Задаем значения редактируемому/создаваемому элементу
    Slot->SetDay(ui->DayBox->currentText());
    Slot->SetTime(ui->TimeBox->currentText());
    Slot->SetWhatWeek(ui->WeekBox->currentText());
    Slot->ChangeIsSet(true);

    //Сортируем, только если элемент редактируемый (иначе сортировку проведет метод добавления в форме редактирования учителя)
    if (flag)
        Parentlist->sortItems();

    this->close();
}


void ChangeWorkSlot::on_DialogButtons_rejected()
{
    this->close();
}

