#ifndef LESSONLISTWIDGETITEM_H
#define LESSONLISTWIDGETITEM_H

#include <QListWidgetItem>

#include "lessons.h"

class LessonListWidgetItem : public QListWidgetItem
{
public:
    LessonListWidgetItem(Lessons *lesson);

    bool operator<(const QListWidgetItem& other) const override;

private:
    Lessons *Lesson;
};

#endif // LESSONLISTWIDGETITEM_H
