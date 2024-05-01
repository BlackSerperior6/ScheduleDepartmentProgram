#include "changesgdata.h"
#include "ui_changesgdata.h"
#include <QMessageBox>

#include "lessons.h"
#include <changelessonform.h>

ChangeSgData::ChangeSgData(QWidget *parent, StudyGroup *group, QListWidget *teachers,
                           QListWidget *parentList) :
    QDialog(parent),
    ui(new Ui::ChangeSgData)
{
    ui->setupUi(this);

    Group = group;
    Teachers = teachers;
    ParentList = parentList;

    ui->NameEdit->setText(group->GetName());
    currentListIndex = -1;

    QListWidget *list = Group->GetLessons();

    for (int i = 0; i < list->count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;

        Lessons *lesson = new Lessons(nullptr, nullptr, nullptr, false);

        *lesson = *((Lessons*) list->itemWidget(list->item(i)));

        ui->LessonsList->addItem(item);
        ui->LessonsList->setItemWidget(item, lesson);
    }
}

ChangeSgData::~ChangeSgData()
{
    delete ui;
}

void ChangeSgData::on_Buttons_accepted()
{
    if (ui->NameEdit->text().isEmpty() || ui->LessonsList->count() == 0)
    {
        QMessageBox::information(this, "Ошибка!", "Одно из полей оказалось пустым");
        return;
    }

    if (ParentList->count() != 0)
    {
        bool flag = false;

        for (int i = 0;i < ParentList->count() && !flag; i++)
        {
            StudyGroup *current = (StudyGroup*) ParentList->itemWidget(ParentList->item(i));

            flag = Group != current &&
                    current->GetName() == ui->NameEdit->text();
        }

        if (flag)
        {
            QMessageBox::information(nullptr, "Ошибка!", "Группа с таким названием уже "
                                                         "есть");
            return;
        }
    }

    Group->SetName(ui->NameEdit->text());

    QListWidget *list = Group->GetLessons();

    list->clear();

    for (int i = 0; i < ui->LessonsList->count(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;

        Lessons *lesson = new Lessons(nullptr, nullptr, nullptr, false);

        *lesson = *((Lessons*) ui->LessonsList->itemWidget(ui->LessonsList->item(i)));

        list->addItem(item);
        list->setItemWidget(item, lesson);
    }

    this->close();
}

void ChangeSgData::on_Buttons_rejected()
{
    this->close();
}

void ChangeSgData::on_LessonsList_itemDoubleClicked(QListWidgetItem *item)
{
    Lessons *lesson = (Lessons*) ui->LessonsList->itemWidget(item);

    ChangeLessonForm *win = new ChangeLessonForm(nullptr, lesson, Teachers, ui->LessonsList);

    win->setModal(true);
    win->exec();
}

void ChangeSgData::on_AddButton_clicked()
{
    QListWidgetItem *item = new QListWidgetItem;
    Lessons *lesson = new Lessons(nullptr, Teachers, ui->LessonsList);

    if (lesson->GetName().isEmpty())
    {
        delete lesson;
        delete item;
        return;
    }

    ui->LessonsList->addItem(item);
    ui->LessonsList->setItemWidget(item, lesson);
}

void ChangeSgData::on_LessonsList_currentRowChanged(int currentRow)
{
    currentListIndex = currentRow;
}

void ChangeSgData::on_RemoveButton_clicked()
{
    if (currentListIndex == -1)
        return;

    QListWidgetItem *it = ui->LessonsList->takeItem(currentListIndex);
    delete it;

    ui->LessonsList->setCurrentRow(-1);
}

