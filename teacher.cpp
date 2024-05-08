#include "teacher.h"
#include "changeteacherfrom.h"

Teacher::Teacher(QWidget *parent, QListWidget *parentList) : QWidget(parent)
{
    Name = new QLabel(this);
    Name->setGeometry(10, 0, 191, 20);

    WorkSlots = new QListWidget;

    ClearScheduel();

    ChangeTeacherFrom *win = new ChangeTeacherFrom(nullptr, this, parentList);

    win->setModal(true);
    win->exec();
}

Teacher::~Teacher()
{
    delete WorkSlots;
}

QListWidget* Teacher::GetWorkSlots()
{
    return WorkSlots;
}

QString Teacher::GetName()
{
    return Name->text();
}

void Teacher::SetName(QString name)
{
    Name->setText(name);
}

std::vector<std::vector<std::vector<Lessons*>>>& Teacher::GetScheduel()
{
    return Scheduel;
}

void Teacher::ClearScheduel()
{
    Scheduel.clear();

    Scheduel = std::vector<std::vector
            <std::vector<Lessons*>>>(6, std::vector<std::vector<Lessons*>>
                                     (6, std::vector<Lessons*>(2, nullptr)));
}
