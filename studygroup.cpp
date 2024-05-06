#include "studygroup.h"
#include "changesgdata.h"

#include <iostream>

StudyGroup::StudyGroup(QWidget *parent, QListWidget *teachers, QListWidget *parentList) : QWidget(parent)
{
    StudyAtSaturday = false;

    Name = new QLabel(this);

    Name->setGeometry(10, 0, 191, 16);

    Les = new QListWidget;

    ClearScheduel();

    ChangeSgData *win = new ChangeSgData(nullptr, this, teachers, parentList);

    win->setModal(true);
    win->exec();
}

StudyGroup::~StudyGroup()
{
    delete Les;
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
    return Les;


}

std::vector<std::vector<std::vector<Lessons*>>>& StudyGroup::GetScheduel()
{
    return Scheduel;
}

void StudyGroup::ClearScheduel()
{
    Scheduel.clear();

    Scheduel = std::vector<std::vector
            <std::vector<Lessons*>>>(6, std::vector<std::vector<Lessons*>>
                                     (6, std::vector<Lessons*>(2, nullptr)));
}

StudyGroup* StudyGroup::GetGroupByName(QString &name, QListWidget *list)
{
    StudyGroup *result = nullptr;

    for (int i = 0; i < list->count() && result == nullptr; i++)
    {
        StudyGroup* current = (StudyGroup*) list->itemWidget(list->item(i));
        if (current->GetName() == name)
            result = current;
    }

    return result;
}
