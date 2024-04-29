#include "scheduledepartment.h"
#include "ui_scheduledepartment.h"

#include "studygroup.h"
#include "changesgdata.h"

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

