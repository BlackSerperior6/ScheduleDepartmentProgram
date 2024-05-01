#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>

#include "workslot.h"

class Teacher : public QWidget
{
    Q_OBJECT
public:
    explicit Teacher(QWidget *parent = nullptr, QListWidget *parentList = nullptr);

    QListWidget* GetWorkSlots();

    QString GetName();

    void SetName(QString name);

private:

    QLabel *Name;

    QListWidget *WorkSlots;

signals:

};

#endif // TEACHER_H
