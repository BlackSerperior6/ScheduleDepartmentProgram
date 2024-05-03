#ifndef STUDYGROUP_H
#define STUDYGROUP_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QListWidget>

#include "lessons.h"

class StudyGroup : public QWidget
{
    Q_OBJECT
public:
    explicit StudyGroup(QWidget *parent = nullptr, QListWidget *teachers = nullptr,
                        QListWidget *parentList = nullptr);

    ~StudyGroup();

    QString GetName();

    QListWidget *GetLessons();

    bool IsStudyingAtSaturdays();

    void SetStudyingAtSaturdays(bool value);

    void SetName(QString name);

    std::vector<std::vector<std::vector<Lessons*>>>& GetScheduel();

    void ClearScheduel();

signals:

private:

    QLabel *Name;

    QListWidget *Les;

    std::vector<std::vector<std::vector<Lessons*>>> Scheduel;

    bool StudyAtSaturday;
};

#endif // STUDYGROUP_H
