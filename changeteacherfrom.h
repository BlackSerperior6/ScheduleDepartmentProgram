#ifndef CHANGETEACHERFROM_H
#define CHANGETEACHERFROM_H

#include <QDialog>

#include "teacher.h"
#include "changeworkslot.h"

namespace Ui {
class ChangeTeacherFrom;
}

class ChangeTeacherFrom : public QDialog //Форма для редактирования педагога
{
    Q_OBJECT

public:
    explicit ChangeTeacherFrom(QWidget *parent = nullptr, Teacher *teacher = nullptr, QListWidget *parentList = nullptr);
    ~ChangeTeacherFrom();

private slots:
    void on_DialogButtons_accepted();

    void on_DialogButtons_rejected();

    void on_WorkSlotsList_itemDoubleClicked(QListWidgetItem *item);

    void on_AddButton_clicked();

    void on_WorkSlotsList_currentRowChanged(int currentRow);

    void on_RemoveButton_clicked();

    void on_ClearButton_clicked();

private:
    Ui::ChangeTeacherFrom *ui;

    Teacher *Teach; //Педагог

    QListWidget *ParentList; //Родительский список педагога

    int WorkSlotsRowSelected;
};

#endif // CHANGETEACHERFROM_H
