#include "studygroup.h"
#include "changesgdata.h"

StudyGroup::StudyGroup(QWidget *parent) : QWidget(parent)
{
    Name = new QLabel(this);
    Scheduel = new QLabel(this);

    Name->setGeometry(0, 0, 61, 16);

    Scheduel->setGeometry(60, 0, 141, 16);

    ChangeSgData *win = new ChangeSgData(nullptr, this);

    win->setModal(true);
    win->exec();
}

void StudyGroup::SetName(QString name)
{
    Name->setText(name);
}

void StudyGroup::SetScheduel(QString scheduel)
{
    Scheduel->setText(scheduel);
}

QString StudyGroup::GetName()
{
    return Name->text();
}

QString StudyGroup::GetScheduel()
{
    return Scheduel->text();
}
