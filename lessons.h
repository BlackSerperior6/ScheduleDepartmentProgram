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

    void operator=(Lessons &lessons);

private:

    QLabel *Name;

    QLabel *TeachersName;

    QLabel *AmountLabel;

    QWidget *Teach;

    int HowManyPerTwoWeeks;

signals:

};

#endif // LESSONS_H
