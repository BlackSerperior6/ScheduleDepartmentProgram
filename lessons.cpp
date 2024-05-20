#include "lessons.h"
#include "teacher.h"

#include "changelessonform.h"

Lessons::Lessons(QWidget *parent, QListWidget *teachersList,
                 QListWidget *parentList, bool shouldCallInterface) : QWidget(parent) //Класс урока
{
    //Задаем геометрию QLabelам, который будут отображать данные урока
    Name = new QLabel(this);
    Name->setGeometry(0, 0, 111, 16);

    TeachersName = new QLabel(this);
    TeachersName->setGeometry(120, 0, 151, 16);

    Teach = nullptr;

    AmountLabel = new QLabel(this);
    AmountLabel->setGeometry(280, 0, 355, 16);

    HowManyPerTwoWeeks = -1;

    //Если требуется вызвать интерфейс редактирования урока
    if (shouldCallInterface)
    {
        //Вызываем
        ChangeLessonForm *win = new ChangeLessonForm(nullptr, this, teachersList, parentList);

        win->setModal(true);
        win->exec();
    }
}

void Lessons::SetName(QString name)
{
    Name->setText(name);
}

void Lessons::SetTeacher(QWidget *teacher)
{
    TeachersName->setText(((Teacher*) teacher)->GetName());

    Teach = teacher;
}

void Lessons::SetHowManyPerTwoWeeks(int amount)
{
    HowManyPerTwoWeeks = amount;
    AmountLabel->setText(QString::number(HowManyPerTwoWeeks));
}

void Lessons::operator=(Lessons &lessons) //Оператор присваивания
{
    SetName(lessons.GetName());
    SetTeacher(lessons.GetTeacher());
    SetHowManyPerTwoWeeks(lessons.GetHowManyPerTwoWeeks());
    SetAttendingGroupName(lessons.GetAttendingGroupName());
}

void Lessons::SetAttendingGroupName(QString name)
{
    AttendingGroupName = name;
}

QString Lessons::GetAttendingGroupName()
{
    return AttendingGroupName;
}

QString Lessons::GetName()
{
    return Name->text();
}

QWidget *Lessons::GetTeacher()
{
    return Teach;
}

int Lessons::GetHowManyPerTwoWeeks()
{
    return HowManyPerTwoWeeks;
}
