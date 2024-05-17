#ifndef LESSONS_H
#define LESSONS_H

#include <QObject>
#include <QLabel>
#include <QListWidget>

class Lessons : public QWidget //Класс урока
{
    Q_OBJECT
public:
    explicit Lessons(QWidget *parent = nullptr, QListWidget *teachersList = nullptr,
                     QListWidget *parentList = nullptr, bool shouldCallInterface = true);

    QString GetName();

    QWidget* GetTeacher();

    void SetName(QString name);

    void SetTeacher(QWidget *teacher);

    int GetHowManyPerTwoWeeks();

    void SetHowManyPerTwoWeeks(int amount);

    void SetAttendingGroupName(QString name);

    QString GetAttandingGroupName();

    void operator=(Lessons &lessons);

private:

    QLabel *Name;

    QLabel *TeachersName;

    QLabel *AmountLabel;

    QWidget *Teach;

    QString AttendingGroupName;

    int HowManyPerTwoWeeks;

signals:

};

#endif // LESSONS_H
