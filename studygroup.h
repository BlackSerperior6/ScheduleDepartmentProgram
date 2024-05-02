#ifndef STUDYGROUP_H
#define STUDYGROUP_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QListWidget>

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

signals:

private:

    QLabel *Name;

    QListWidget *Lessons;

    bool StudyAtSaturday;
};

#endif // STUDYGROUP_H
