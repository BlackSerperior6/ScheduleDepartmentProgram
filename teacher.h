#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>

#include "workslot.h"
#include "lessons.h"

class Teacher : public QWidget //Класс учителя
{
    Q_OBJECT
public:
    explicit Teacher(QWidget *parent = nullptr, QListWidget *parentList = nullptr);

    ~Teacher();

    QListWidget* GetWorkSlots();

    QString GetName();

    std::vector<std::vector<std::vector<Lessons*>>>& GetScheduel();

    void ClearScheduel();

    void SetName(QString name);

private:

    QLabel *Name; //Имя учителя

    QListWidget *WorkSlots; //Список его рабочего времени

    std::vector<std::vector<std::vector<Lessons*>>> Scheduel; //Расписание учителя

signals:

};

#endif // TEACHER_H
