#include "scheduledepartment.h"
#include "ui_scheduledepartment.h"

#include "studygroup.h"
#include "teacher.h"
#include "changesgdata.h"
#include "changeteacherfrom.h"

#include <QMessageBox>

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
    QListWidgetItem *item = new QListWidgetItem;
    StudyGroup *group = new StudyGroup;

    if(group->GetName().isEmpty() || group->GetScheduel().isEmpty())
        return;

    ui->StudyGroupList->addItem(item);
    ui->StudyGroupList->setItemWidget(item, group);
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

    ChangeSgData *win = new ChangeSgData(nullptr, group);

    win->setModal(true);
    win->exec();
}

void ScheduleDepartment::on_AddTeacherButton_clicked()
{
    QListWidgetItem *item = new QListWidgetItem;
    Teacher *teach = new Teacher(nullptr, ui->TeacherList);

    if(teach->GetName().isEmpty() || teach->GetWorkSlots()->count() == 0)
    {
        QMessageBox::information(nullptr, "Ошибка", "Не указано ФИО или рабочее время");

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

