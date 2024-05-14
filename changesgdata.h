#ifndef CHANGESGDATA_H
#define CHANGESGDATA_H

#include <QDialog>
#include <QListWidget>

#include "studygroup.h"

namespace Ui {
class ChangeSgData;
}

class ChangeSgData : public QDialog //Форма редактирования учебной группы
{
    Q_OBJECT

public:
    explicit ChangeSgData(QWidget *parent = nullptr, StudyGroup *group = nullptr,
                          QListWidget *teachers = nullptr,
                          QListWidget *parentList = nullptr);
    ~ChangeSgData();

private slots:
    void on_Buttons_accepted();

    void on_Buttons_rejected();

    void on_LessonsList_itemDoubleClicked(QListWidgetItem *item);

    void on_AddButton_clicked();

    void on_LessonsList_currentRowChanged(int currentRow);

    void on_RemoveButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::ChangeSgData *ui;

    StudyGroup *Group; //Редактируемая группа

    QListWidget *Teachers; //Список всех заданных программе учителей

    QListWidget *ParentList; //Список, из которого был получен элемент

    int currentListIndex; //Индес выбранного элемента с списке предметов
};

#endif // CHANGESGDATA_H
