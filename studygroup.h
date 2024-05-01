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

    QString GetName();

    QListWidget *GetLessons();

    void SetName(QString name);

signals:

private:

    QLabel *Name;

    QListWidget *Lessons;
};

#endif // STUDYGROUP_H
