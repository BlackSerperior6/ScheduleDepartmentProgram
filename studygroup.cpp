#include "studygroup.h"
#include "changesgdata.h"

StudyGroup::StudyGroup(QWidget *parent, QListWidget *teachers, QListWidget *parentList) : QWidget(parent)
{
    Name = new QLabel(this);

    Name->setGeometry(10, 0, 191, 16);

    Lessons = new QListWidget;

    ChangeSgData *win = new ChangeSgData(nullptr, this, teachers, parentList);

    win->setModal(true);
    win->exec();
}

void StudyGroup::SetName(QString name)
{
    Name->setText(name);
}

QString StudyGroup::GetName()
{
    return Name->text();
}

QListWidget *StudyGroup::GetLessons()
{
    return Lessons;
}
