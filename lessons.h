#ifndef LESSONS_H
#define LESSONS_H

#include <QObject>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <vector>

class Lessons : public QWidget
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

    void ClearAttendingGroupsNames();

    bool CanBeMerged();

    void CanBeMerged(bool value);

    std::vector<QString>& GetAttendingGroupsNames();

    void operator=(Lessons &lessons);

private:

    QLabel *Name;

    QLabel *TeachersName;

    QLabel *AmountLabel;

    QWidget *Teach;

    int HowManyPerTwoWeeks;

    bool AllowMerged;

    std::vector<QString> AttendingGroupsNames;

signals:

};

#endif // LESSONS_H
