#include "changelessonform.h"
#include "ui_changelessonform.h"

#include "lessons.h"
#include "teacher.h"

#include <QMessageBox>

ChangeLessonForm::ChangeLessonForm(QWidget *parent, Lessons *lesson, QListWidget *teachers,
                                   QListWidget *parentList) :
    QDialog(parent),
    ui(new Ui::ChangeLessonForm)
{
    ui->setupUi(this);

    Lesson = lesson;
    Teachers = teachers;
    ParentList = parentList;

    //Задаем TextEditу название редактируемого урока
    ui->NameEdit->setText(Lesson->GetName());

    int setindex = -1;

    for (int i = 0; i < teachers->count(); i++)
    {
        Teacher *current = (Teacher*) teachers->itemWidget(teachers->item(i));

        ui->TeacherList->addItem(current->GetName());

        if (Lesson->GetTeacher() == current)
            setindex = i;
    }

    //Задаем преподователя, который на момент редактирования ввел урок (задаем первого в списке, если никто не ввел)
    if (setindex != -1)
        ui->TeacherList->setCurrentIndex(setindex);

    if(Lesson->GetHowManyPerTwoWeeks() != -1) //Задаем кол-во пар на две недели (1 по умолчанию)
        ui->AmountBox->setValue(Lesson->GetHowManyPerTwoWeeks());
}

ChangeLessonForm::~ChangeLessonForm()
{
    delete ui;
}

void ChangeLessonForm::on_DialogButtons_accepted()
{
    if (ui->NameEdit->text().isEmpty()) //Если поле имени пусто, то сообщаем о ошибке
    {
        QMessageBox::information(nullptr, "Ошибка!", "Поле названия не может быть пустым!");
        return;
    }

    QString name = ui->NameEdit->text();

    if (ParentList->count() != 0) //Проверка на то, что списке группы нету уже урока с таким названием
    {
        bool flag = false;

        for (int i = 0; i < ParentList->count() && !flag; i++)
        {
            Lessons *current = (Lessons*) ParentList->itemWidget(ParentList->item(i));

            flag = current != Lesson && current->GetName() == name;
        }

        if (flag) //Если есть, то сообщаем о ошибке
        {
            QMessageBox::information(nullptr, "Ошибка!", "Урок с таким названием уже есть!");
            return;
        }
    }

    //Флаг. обозначающий, что элемент именно редактируют, а не создают новый
    bool flag = !Lesson->GetName().isEmpty();

    Lesson->SetName(name);

    bool flag2 = false;

    Teacher *chosenTeacher;

    for (int i = 0; i < Teachers->count() && !flag2; i++) //Задаем учителя с указанным в форме именем
    {
        Teacher* current = (Teacher*) Teachers->itemWidget(Teachers->item(i));

        flag2 = current->GetName() ==
                ui->TeacherList->currentText();

        if (flag2)
            chosenTeacher = current;
    }

    Lesson->SetTeacher(chosenTeacher); //Задаем учителя

    Lesson->SetHowManyPerTwoWeeks(ui->AmountBox->value()); //Задаем кол-во пар на 2 недели

    if (flag) //Если элемент именно отредатировали, а нед добавили, то сортируем родительский список
        ParentList->sortItems(Qt::DescendingOrder);

    this->close(); //Закрываем интерфейс
}

void ChangeLessonForm::on_DialogButtons_rejected()
{
    this->close(); //В случае отказа от редактирования закрываем интерфейс
}
