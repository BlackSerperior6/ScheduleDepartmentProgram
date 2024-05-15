#ifndef SCHEDULEDEPARTMENT_H
#define SCHEDULEDEPARTMENT_H
#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class ScheduleDepartment; }
QT_END_NAMESPACE

class ScheduleDepartment : public QMainWindow
{
    Q_OBJECT

public:
    ScheduleDepartment(QWidget *parent = nullptr);
    ~ScheduleDepartment();

private slots:
    void on_AddStudyGroupButton_clicked();

    void on_RemoveStudyGroupButton_clicked();

    void on_StudyGroupList_currentRowChanged(int currentRow);

    void on_ClearSudyGroupButton_clicked();

    void on_StudyGroupList_itemDoubleClicked(QListWidgetItem *item);

    void on_AddTeacherButton_clicked();

    void on_TeacherList_currentRowChanged(int currentRow);

    void on_RemoveTeacherButton_clicked();

    void on_TeacherList_itemDoubleClicked(QListWidgetItem *item);

    void on_GenerateScheduelButton_clicked();

    void on_ChooseFolderButton_clicked();

private:
    Ui::ScheduleDepartment *ui;

    int StudentGroupsRowSelected;
    int TeachersGroupsRowSelected;

    QString FilePath; //Путь для вывода реpультата программы
};
#endif // SCHEDULEDEPARTMENT_H
