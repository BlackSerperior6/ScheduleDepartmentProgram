#include "changesgdata.h"
#include "ui_changesgdata.h"

#include <QMessageBox>

#include "lessons.h"
#include "lessonlistwidgetitem.h"
#include <changelessonform.h>

ChangeSgData::ChangeSgData(QWidget *parent, StudyGroup *group, QListWidget *teachers,
                           QListWidget *parentList) :
    QDialog(parent),
    ui(new Ui::ChangeSgData)
{
    ui->setupUi(this);

    //Записываем данные: группа, учителя, родительский лист
    Group = group;
    Teachers = teachers;
    ParentList = parentList;

    //Задавание данных в элементы ui: название группы и учится ли она в субботу
    ui->NameEdit->setText(Group->GetName());
    ui->StudyAtSaturday->setChecked(Group->IsStudyingAtSaturdays());
    currentListIndex = -1;

    QListWidget *list = Group->GetLessons();

    //Переносим в список ui все предметы группыю. UI список служит буффером
    for (int i = 0; i < list->count(); i++)
    {
        Lessons *lesson = new Lessons(nullptr, nullptr, nullptr, false);
        LessonListWidgetItem *item = new LessonListWidgetItem(lesson);

        //Причем элементы не переносятся, а именно что копируются в буффер - список
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
    if (ui->NameEdit->text().isEmpty()) //НУ группы должно быть имя
    {
        QMessageBox::information(this, "Ошибка!", "У группы должно быть имя");
        return;
    }

    if (ui->LessonsList->count() == 0) //У группы должны быть пары
    {
        QMessageBox::information(this, "Ошибка!", "У группы должна быть хотя бы одна пара");
        return;
    }

    if (ParentList->count() != 0) //Если родительский список не пуст
    {
        bool flag = false;

        for (int i = 0;i < ParentList->count() && !flag; i++) //Проверка на то, что группы с таким именнем нет
        {
            StudyGroup *current = (StudyGroup*) ParentList->itemWidget(ParentList->item(i));

            flag = Group != current &&
                    current->GetName() == ui->NameEdit->text();
        }

        if (flag) //Если есть, то выдает сообщение о ошибке
        {
            QMessageBox::information(nullptr, "Ошибка!", "Группа с таким названием уже "
                                                         "есть");
            return;
        }
    }

    Group->SetName(ui->NameEdit->text()); //Задаем группе имя
    Group->SetStudyingAtSaturdays(ui->StudyAtSaturday->isChecked()); //Задаем учится ли группа в субботу

    QListWidget *list = Group->GetLessons();

    list->clear();

    //Переносим все элементы из списка - буффера в реальный список предметов группы
    for (int i = 0; i < ui->LessonsList->count(); i++)
    {
        Lessons *lesson = new Lessons(nullptr, nullptr, nullptr, false);
        LessonListWidgetItem *item = new LessonListWidgetItem(lesson);

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
    //При двойном нажатии кнопки мыши по элементу открываем окно редактирования

    Lessons *lesson = (Lessons*) ui->LessonsList->itemWidget(item);

    ChangeLessonForm *win = new ChangeLessonForm(nullptr, lesson, Teachers, ui->LessonsList);

    win->setModal(true);
    win->exec();
}

void ChangeSgData::on_AddButton_clicked()
{
    //Создаем новый экземляр класс Lessons
    Lessons *lesson = new Lessons(nullptr, Teachers, ui->LessonsList);

    LessonListWidgetItem *item = new LessonListWidgetItem(lesson);

    //Если по итогу добавление было отменено
    if (lesson->GetName().isEmpty())
    {
        //Чистим память
        delete lesson;
        delete item;
        return;
    }

    //Добавляем урок в список
    ui->LessonsList->addItem(item);
    ui->LessonsList->setItemWidget(item, lesson);
    ui->LessonsList->sortItems(Qt::DescendingOrder);
}

void ChangeSgData::on_LessonsList_currentRowChanged(int currentRow)
{
    currentListIndex = currentRow;
}

void ChangeSgData::on_RemoveButton_clicked()
{
    if (currentListIndex == -1)
        return;

    //Удаляем выбранный экземпляр
    QListWidgetItem *it = ui->LessonsList->takeItem(currentListIndex);
    delete it;

    ui->LessonsList->setCurrentRow(-1);
}

void ChangeSgData::on_ClearButton_clicked()
{
    ui->LessonsList->clear();
}
