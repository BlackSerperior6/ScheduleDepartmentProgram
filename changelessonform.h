#ifndef CHANGELESSONFORM_H
#define CHANGELESSONFORM_H

#include <QDialog>

#include "lessons.h"

#include <QListWidget>

namespace Ui {
class ChangeLessonForm;
}

class ChangeLessonForm : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeLessonForm(QWidget *parent = nullptr, Lessons *lesson = nullptr,
                              QListWidget *teachers = nullptr, QListWidget *parentList = nullptr);
    ~ChangeLessonForm();

private slots:
    void on_DialogButtons_accepted();

    void on_DialogButtons_rejected();

private:
    Ui::ChangeLessonForm *ui;

    Lessons *Lesson;

    QListWidget *ParentList;

    QListWidget *Teachers;
};

#endif // CHANGELESSONFORM_H
