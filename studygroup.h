#ifndef STUDYGROUP_H
#define STUDYGROUP_H

#include <QWidget>
#include <QString>
#include <QLabel>

class StudyGroup : public QWidget
{
    Q_OBJECT
public:
    explicit StudyGroup(QWidget *parent = nullptr);

    QString GetName();

    QString GetScheduel();

    void SetName(QString name);

    void SetScheduel(QString scheduel);

signals:

private:

    QLabel *Name;

    QLabel *Scheduel;
};

#endif // STUDYGROUP_H
