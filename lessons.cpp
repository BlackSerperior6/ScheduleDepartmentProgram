#include "lessons.h"
#include "teacher.h"

#include "changelessonform.h"

Lessons::Lessons(QWidget *parent, QListWidget *teachersList,
                 QListWidget *parentList, bool shouldCallInterface) : QWidget(parent)
{
    Name = new QLabel(this);
    Name->setGeometry(0, 0, 111, 16);

    TeachersName = new QLabel(this);
    TeachersName->setGeometry(120, 0, 151, 16);

    Teach = nullptr;

    AmountLabel = new QLabel(this);
    AmountLabel->setGeometry(280, 0, 355, 16);

    HowManyPerTwoWeeks = -1;

    if (shouldCallInterface)
    {
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
    Teacher* teach = (Teacher*) teacher;

    TeachersName->setText(teach->GetName());
    Teach = teacher;
}

void Lessons::SetHowManyPerTwoWeeks(int amount)
{
    HowManyPerTwoWeeks = amount;
    AmountLabel->setText(QString::number(HowManyPerTwoWeeks));
}

void Lessons::operator=(Lessons &lessons)
{
    SetName(lessons.GetName());
    SetTeacher(lessons.GetTeacher());
    SetHowManyPerTwoWeeks(lessons.GetHowManyPerTwoWeeks());
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
