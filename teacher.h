#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>

#include <vector>

#include "workslot.h"
#include <TeacherScheduelElement.h>

class Teacher : public QWidget
{
    Q_OBJECT
public:
    explicit Teacher(QWidget *parent = nullptr, QListWidget *parentList = nullptr);

    ~Teacher();

    QListWidget* GetWorkSlots();

    QString GetName();

    std::vector<std::vector<std::vector<ScheduelTeacherElement>>>& GetScheduel();

    void ClearScheduel();

    void SetName(QString name);

private:

    QLabel *Name;

    QListWidget *WorkSlots;

    std::vector<std::vector<std::vector<ScheduelTeacherElement>>> Scheduel;

signals:

};

#endif // TEACHER_H
