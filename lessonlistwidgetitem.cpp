#include "lessonlistwidgetitem.h"

LessonListWidgetItem::LessonListWidgetItem(Lessons *lesson)
{
    Lesson = lesson; //Задаем урок, пренадлежащий этому элементу
}

bool LessonListWidgetItem::operator<(const QListWidgetItem &other) const
{
    //Перегруженный оператор <. Вернет true, если кол-во пар текущего урока меньше, чем того, с которым сверяем
    return Lesson->GetHowManyPerTwoWeeks() <
            static_cast<const LessonListWidgetItem&>(other).Lesson->GetHowManyPerTwoWeeks();
}


