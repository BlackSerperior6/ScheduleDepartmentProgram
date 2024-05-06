#ifndef TEACHERSCHEDUELELEMENT_H
#define TEACHERSCHEDUELELEMENT_H

#include "lessons.h"
#include <vector>

struct ScheduelTeacherElement
{
    Lessons* lesson = nullptr;
    std::vector<QString> AttendingGroupsNames;

    bool IsAlreadyAttending(QString name)
    {
        bool result = false;

        for (int i = 0; i < AttendingGroupsNames.size(); i++)
            result = AttendingGroupsNames[i] == name;

        return result;

    }
};

#endif // TEACHERSCHEDUELELEMENT_H
