#ifndef LESSONLISTWIDGETITEM_H
#define LESSONLISTWIDGETITEM_H

#include <QListWidgetItem>

#include "lessons.h"

class LessonListWidgetItem : public QListWidgetItem //Элемент списка предметов
{
public:
    LessonListWidgetItem(Lessons *lesson);

    bool operator<(const QListWidgetItem& other) const override;

private:
    Lessons *Lesson; //Присовеный элементу урок
};

#endif // LESSONLISTWIDGETITEM_H
