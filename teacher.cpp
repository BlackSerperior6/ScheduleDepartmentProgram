#include "teacher.h"
#include "changeteacherfrom.h"

Teacher::Teacher(QWidget *parent, QListWidget *parentList) : QWidget(parent)
{
    Name = new QLabel(this);
    Name->setGeometry(10, 0, 191, 20);

    WorkSlots = new QListWidget;

    ChangeTeacherFrom *win = new ChangeTeacherFrom(nullptr, this, parentList);

    win->setModal(true);
    win->exec();
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
