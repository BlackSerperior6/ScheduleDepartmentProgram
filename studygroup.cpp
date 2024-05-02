#include "studygroup.h"
#include "changesgdata.h"

#include <iostream>

StudyGroup::StudyGroup(QWidget *parent, QListWidget *teachers, QListWidget *parentList) : QWidget(parent)
{
    StudyAtSaturday = false;

    Name = new QLabel(this);

    Name->setGeometry(10, 0, 191, 16);

    Lessons = new QListWidget;

    ChangeSgData *win = new ChangeSgData(nullptr, this, teachers, parentList);

    win->setModal(true);
    win->exec();
}

StudyGroup::~StudyGroup()
{
    delete Lessons;
}

void StudyGroup::SetName(QString name)
{
    Name->setText(name);
}

void StudyGroup::SetStudyingAtSaturdays(bool value)
{
    StudyAtSaturday = value;
}

bool StudyGroup::IsStudyingAtSaturdays()
{
    return StudyAtSaturday;
}

QString StudyGroup::GetName()
{
    return Name->text();
}

QListWidget *StudyGroup::GetLessons()
{
    return Lessons;
}
