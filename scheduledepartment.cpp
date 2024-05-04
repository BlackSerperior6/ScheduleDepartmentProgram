#include "scheduledepartment.h"
#include "ui_scheduledepartment.h"

#include "studygroup.h"
#include "teacher.h"
#include "changesgdata.h"
#include "changeteacherfrom.h"
#include "lessons.h"

#include <QMessageBox>
#include <fstream>
#include <iostream>

ScheduleDepartment::ScheduleDepartment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScheduleDepartment)
{
    ui->setupUi(this);
    StudentGroupsRowSelected = -1;
    TeachersGroupsRowSelected = -1;
}

ScheduleDepartment::~ScheduleDepartment()
{
    delete ui;
}

void ScheduleDepartment::on_AddStudyGroupButton_clicked()
{
    if (ui->TeacherList->count() == 0)
    {
        QMessageBox::information(nullptr, "Ошибка!",
                                 "Перед добавление группы добавьте хотя бы одного учителя");
        return;
    }

    QListWidgetItem *item = new QListWidgetItem;
    StudyGroup *group = new StudyGroup(nullptr, ui->TeacherList, ui->StudyGroupList);

    if (group->GetName().isEmpty() || group->GetLessons()->count() == 0)
        return;

    ui->StudyGroupList->addItem(item);
    ui->StudyGroupList->setItemWidget(item, group);
    ui->StudyGroupList->sortItems();
}

void ScheduleDepartment::on_RemoveStudyGroupButton_clicked()
{
    if (StudentGroupsRowSelected == -1)
        return;

    QListWidgetItem *it = ui->StudyGroupList->takeItem(StudentGroupsRowSelected);
    delete it;

    ui->StudyGroupList->setCurrentRow(-1);
}

void ScheduleDepartment::on_StudyGroupList_currentRowChanged(int currentRow)
{
    StudentGroupsRowSelected = currentRow;
}

void ScheduleDepartment::on_ClearSudyGroupButton_clicked()
{
    ui->StudyGroupList->clear();
}

void ScheduleDepartment::on_StudyGroupList_itemDoubleClicked(QListWidgetItem *item)
{
    StudyGroup *group =  (StudyGroup*) ui->StudyGroupList->itemWidget(item);

    ChangeSgData *win = new ChangeSgData(nullptr, group, ui->TeacherList, ui->StudyGroupList);

    win->setModal(true);
    win->exec();
}

void ScheduleDepartment::on_AddTeacherButton_clicked()
{
    QListWidgetItem *item = new QListWidgetItem;
    Teacher *teach = new Teacher(nullptr, ui->TeacherList);

    if(teach->GetName().isEmpty() || teach->GetWorkSlots()->count() == 0)
    {
        delete teach;
        delete item;
        return;
    }

    ui->TeacherList->addItem(item);
    ui->TeacherList->setItemWidget(item, teach);
}

void ScheduleDepartment::on_TeacherList_currentRowChanged(int currentRow)
{
    TeachersGroupsRowSelected = currentRow;
}

void ScheduleDepartment::on_RemoveTeacherButton_clicked()
{
    if (TeachersGroupsRowSelected == -1)
        return;

    bool flag = false;

    for (int i = 0; i < ui->StudyGroupList->count() && !flag; i++)
    {
        StudyGroup* group = (StudyGroup*)
                ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));

        for (int j = 0; j < group->GetLessons()->count() && !flag; j++)
        {
            Lessons* current = (Lessons*) group->GetLessons()->
                    itemWidget(group->GetLessons()->item(j));

            flag = ((Teacher*) current->GetTeacher())->GetName() ==
                    ((Teacher*)
                     ui->TeacherList->
                     itemWidget(ui->TeacherList->item(TeachersGroupsRowSelected)))->GetName();

            if (flag)
                QMessageBox::information(nullptr, "Ошибка",
                                         "Данный предодователь преподает в группе "
                                         + group->GetName() + ", невозможно удаление!");
        }
    }

    if (flag)
        return;

    QListWidgetItem *it = ui->TeacherList->takeItem(TeachersGroupsRowSelected);
    delete it;

    ui->TeacherList->setCurrentRow(-1);
}

void ScheduleDepartment::on_TeacherList_itemDoubleClicked(QListWidgetItem *item)
{
    Teacher *teach =  (Teacher*) ui->TeacherList->itemWidget(item);

    ChangeTeacherFrom *win = new ChangeTeacherFrom(nullptr, teach, ui->TeacherList);

    win->setModal(true);
    win->exec();
}


void ScheduleDepartment::on_GenerateScheduelButton_clicked()
{
    if (ui->TeacherList->count() == 0)
    {
        QMessageBox::information(nullptr, "Ошибка!", "Вы не указали ни одного преподователя");
        return;
    }

    if (ui->StudyGroupList->count() == 0)
    {
        QMessageBox::information(nullptr, "Ошибка!", "Вы не указали ни одной группы");
        return;
    }

    bool mainFlag = true; //true - пока рассписание составлять можно

    for (int i = 0; i < ui->StudyGroupList->count() && mainFlag; i++)
    {
        StudyGroup *currentSg = (StudyGroup*)
                ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));

        for (int j = 0; j < currentSg->GetLessons()->count() && mainFlag; j++)
        {
            Lessons* currentLesson = (Lessons*)
                    currentSg->GetLessons()->itemWidget(currentSg->GetLessons()->item(j));

            for (int k = 0; k < currentLesson->GetHowManyPerTwoWeeks() && mainFlag; k++)
            {
                Teacher* currentTeacher = (Teacher*) currentLesson->GetTeacher();

                bool subFlag = false; //Получилось найти место под урок

                for (int p = 0; p < currentTeacher->GetWorkSlots()->count() && !subFlag; p++)
                {
                    WorkSlot* currentWorkSlot = (WorkSlot*)
                            currentTeacher->GetWorkSlots()
                            ->itemWidget(currentTeacher->GetWorkSlots()->item(p));

                    ParsedWorkSlot slot = currentWorkSlot->ParseToIndexes();

                    bool NoProblemWithTheGroup = currentSg->GetScheduel()[slot.DayIndex]
                            [slot.TimeIndex][slot.WeekIndex] == nullptr &&
                            (slot.DayIndex != 5 || currentSg->IsStudyingAtSaturdays());

                    if (currentTeacher->GetScheduel()[slot.DayIndex]
                            [slot.TimeIndex][slot.WeekIndex]
                            == nullptr && NoProblemWithTheGroup)
                    {

                        currentTeacher->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex] = currentLesson;

                        currentSg->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex] = currentLesson;

                        currentLesson->GetAttendingGroupsNames().push_back(currentSg->GetName());

                        subFlag = true;
                    }
                }

                if (!subFlag)
                {
                    for (int p = 0; p < currentTeacher->GetWorkSlots()->count() && !subFlag; p++)
                    {
                        WorkSlot* currentWorkSlot = (WorkSlot*)
                                currentTeacher->GetWorkSlots()
                                ->itemWidget(currentTeacher->GetWorkSlots()->item(p));

                        ParsedWorkSlot slot = currentWorkSlot->ParseToIndexes();

                        bool NoProblemWithTheGroup = currentSg->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex] == nullptr &&
                                (slot.DayIndex != 5 || currentSg->IsStudyingAtSaturdays());


                        if (NoProblemWithTheGroup && currentTeacher->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex] != nullptr
                                && currentTeacher->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex]->GetName() == currentLesson->GetName())
                        {
                            currentSg->GetScheduel()[slot.DayIndex]
                                    [slot.TimeIndex][slot.WeekIndex] = currentTeacher
                                    ->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex];

                            currentTeacher->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex]
                                    ->GetAttendingGroupsNames().push_back(currentSg->GetName());

                            subFlag = true;
                        }
                    }
                }

                mainFlag = subFlag;
            }
        }
    }

    if (!mainFlag)
        QMessageBox::information(nullptr, "Ошибка!",
                                 "Невозможно составить рассписание при таких входных данных");
    else
    {
        for (int i = 0; i < ui->StudyGroupList->count(); i++)
        {
            StudyGroup* current = (StudyGroup*) ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));

            std::ofstream stream(current->GetName().toStdString() + ".txt");

            for (int j = 0; j < 6; j++)
            {
                switch (j)
                {
                case 0:
                    stream << "Понедельник:";
                    break;
                case 1:
                    stream << "Вторник:";
                    break;
                case 2:
                    stream << "Среда:";
                    break;
                case 3:
                    stream << "Четверг:";
                    break;
                case 4:
                    stream << "Пятница:";
                    break;
                case 5:
                    stream << "Суббота:";
                    break;
                }

                stream << "\n";

                for (int k = 0; k < 6; k++)
                {
                    stream << "  ";

                    switch (k)
                    {
                    case 0:
                        stream << "8:00:";
                        break;
                    case 1:
                        stream << "9:40:";
                        break;
                    case 2:
                        stream << "11:30";
                        break;
                    case 3:
                        stream << "13:20:";
                        break;
                    case 4:
                        stream << "15:00";
                        break;
                    case 5:
                        stream << "16:40";
                        break;
                    }

                    stream << "\n";

                    for (int u = 0; u < 2; u++)
                    {
                        stream << "         ";

                        switch (u)
                        {
                        case 0:
                            stream << "1-ая неделя:";
                            break;
                        case 1:
                            stream << "2-ая неделя:";
                            break;
                        }

                        if (current->GetScheduel()[j][k][u] != nullptr)
                            stream << "  " +  current->GetScheduel()[j][k][u]->GetName().toStdString() +
                                      "  " + "(" + ((Teacher*) current->GetScheduel()[j][k][u]->GetTeacher())->GetName()
                                      .toStdString() + ")";

                        stream << "\n";
                    }
                }

                stream << "\n\n\n";
            }

            stream.close();
        }

        for (int i = 0; i < ui->TeacherList->count(); i++)
        {
            Teacher* current = (Teacher*) ui->TeacherList->itemWidget(ui->TeacherList->item(i));

            std::ofstream stream(current->GetName().toStdString() + ".txt");

            for (int j = 0; j < 6; j++)
            {
                switch (j)
                {
                case 0:
                    stream << "Понедельник:";
                    break;
                case 1:
                    stream << "Вторник:";
                    break;
                case 2:
                    stream << "Среда:";
                    break;
                case 3:
                    stream << "Четверг:";
                    break;
                case 4:
                    stream << "Пятница:";
                    break;
                case 5:
                    stream << "Суббота:";
                    break;
                }

                stream << "\n";

                for (int k = 0; k < 6; k++)
                {
                    stream << "  ";

                    switch (k)
                    {
                    case 0:
                        stream << "8:00:";
                        break;
                    case 1:
                        stream << "9:40:";
                        break;
                    case 2:
                        stream << "11:30";
                        break;
                    case 3:
                        stream << "13:20:";
                        break;
                    case 4:
                        stream << "15:00";
                        break;
                    case 5:
                        stream << "16:40";
                        break;
                    }

                    stream << "\n";

                    for (int u = 0; u < 2; u++)
                    {
                        stream << "         ";

                        switch (u)
                        {
                        case 0:
                            stream << "1-ая неделя:";
                            break;
                        case 1:
                            stream << "2-ая неделя:";
                            break;
                        }

                        if (current->GetScheduel()[j][k][u] != nullptr)
                        {
                            QString Groups = "(" + current->GetScheduel()[j][k][u]->GetAttendingGroupsNames()[0];

                            for (int i = 1; i < current->GetScheduel()[j][k][u]->GetAttendingGroupsNames().size();
                                 i++)
                                Groups += "; " + current->GetScheduel()[j][k][u]->GetAttendingGroupsNames()[i];

                            Groups += ")";

                            stream << "  " +  current->GetScheduel()[j][k][u]->GetName().toStdString() +
                                      "  " + Groups.toStdString();
                        }

                        stream << "\n";
                    }
                }

                stream << "\n\n\n";
            }

            stream.close();
        }

        QMessageBox::information(nullptr, "Ура!", "Рассписание для всех групп и учителей было"
                                                  "успешно создано!");
    }

    for (int i = 0; i < ui->StudyGroupList->count() ; i++)
    {
        StudyGroup *current = (StudyGroup*) ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));
        current->ClearScheduel();

        for (int j = 0; j < current->GetLessons()->count(); j++)
        {
            ((Lessons*) current->GetLessons()->
                    itemWidget(current->GetLessons()->item(j)))
                    ->ClearAttendingGroupsNames();
        }
    }

    for (int i = 0; i < ui->TeacherList->count(); i++)
        ((Teacher*) ui->TeacherList->itemWidget(ui->TeacherList->item(i)))->ClearScheduel();
}

