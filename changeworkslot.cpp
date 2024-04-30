#include "changeworkslot.h"
#include "ui_changeworkslot.h"

#include <QMessageBox>
#include <iostream>

ChangeWorkSlot::ChangeWorkSlot(QWidget *parent, WorkSlot *slot, QListWidget *parentlist) :
    QDialog(parent),
    ui(new Ui::ChangeWorkSlot)
{
    ui->setupUi(this);

    Slot = slot;
    Parentlist = parentlist;

    bool flag = false;

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

    for (int i = 0; i < Parentlist->count() && !flag; i++)
    {
        WorkSlot *current = (WorkSlot*)
                Parentlist->itemWidget(
                    Parentlist->item(i));

        flag = Slot != current && current->Compare(ui->DayBox->currentText(),
                                ui->TimeBox->currentText(),
                                ui->WeekBox->currentText());
    }

    if (flag)
    {
        QMessageBox::information(nullptr, "Ошибка!",
                                 "Такой элемент уже есть в списке");

        Slot->ChangeIsSet(false);
        return;
    }

    Slot->SetDay(ui->DayBox->currentText());
    Slot->SetTime(ui->TimeBox->currentText());
    Slot->SetWhatWeek(ui->WeekBox->currentText());
    Slot->ChangeIsSet(true);
    this->close();
}


void ChangeWorkSlot::on_DialogButtons_rejected()
{
    Slot->ChangeIsSet(false);
    this->close();
}

