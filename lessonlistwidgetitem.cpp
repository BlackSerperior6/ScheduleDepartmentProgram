#include "lessonlistwidgetitem.h"

LessonListWidgetItem::LessonListWidgetItem(Lessons *lesson)
{
    Lesson = lesson;
}

bool LessonListWidgetItem::operator<(const QListWidgetItem &other) const
{
    return Lesson->GetHowManyPerTwoWeeks() <
            static_cast<const LessonListWidgetItem&>(other).Lesson->GetHowManyPerTwoWeeks();
}


