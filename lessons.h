#ifndef LESSONS_H
#define LESSONS_H

#include <QObject>
#include <QLabel>

#include "teacher.h"

class Lessons : public QWidget
{
    Q_OBJECT
public:
    explicit Lessons(QWidget *parent = nullptr, QListWidget *teachersList = nullptr,
                     QListWidget *parentList = nullptr, bool shouldCallInterface = true);

    QString GetName();

    Teacher* GetTeacher();

    void SetName(QString name);

    void SetTeacher(Teacher *teacher);

    int GetHowManyPerTwoWeeks();

    void SetHowManyPerTwoWeeks(int amount);

    void operator=(Lessons &lessons);

private:

    QLabel *Name;

    QLabel *TeachersName;

    QLabel *AmountLabel;

    Teacher *Teach;

    int HowManyPerTwoWeeks;

signals:

};

#endif // LESSONS_H
