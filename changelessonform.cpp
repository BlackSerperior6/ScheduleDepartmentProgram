#include "changelessonform.h"
#include "ui_changelessonform.h"

#include "lessons.h"

#include <QMessageBox>

ChangeLessonForm::ChangeLessonForm(QWidget *parent, Lessons *lesson, QListWidget *teachers,
                                   QListWidget *parentList) :
    QDialog(parent),
    ui(new Ui::ChangeLessonForm)
{
    ui->setupUi(this);

    Lesson = lesson;
    Teachers = teachers;
    ParentList = parentList;

    ui->NameEdit->setText(Lesson->GetName());

    int setindex = -1;

    for (int i = 0; i < teachers->count(); i++)
    {
        Teacher *current = (Teacher*) teachers->itemWidget(teachers->item(i));

        ui->TeacherList->addItem(current->GetName());

        if (Lesson->GetTeacher() == current)
            setindex = i;
    }

    if (setindex != -1)
        ui->TeacherList->setCurrentIndex(setindex);

    if(Lesson->GetHowManyPerTwoWeeks() != -1)
        ui->AmountBox->setValue(Lesson->GetHowManyPerTwoWeeks());
}

ChangeLessonForm::~ChangeLessonForm()
{
    delete ui;
}

void ChangeLessonForm::on_DialogButtons_accepted()
{
    if (ui->NameEdit->text().isEmpty())
    {
        QMessageBox::information(nullptr, "Ошибка!", "Поле имени не может быть пустым!");
        return;
    }

    QString name = ui->NameEdit->text();

    if (ParentList->count() != 0)
    {
        bool flag = false;

        for (int i = 0; i < ParentList->count() && !flag; i++)
        {
            Lessons *current = (Lessons*) ParentList->itemWidget(ParentList->item(i));

            flag = current != Lesson && current->GetName() == name;
        }

        if (flag)
        {
            QMessageBox::information(nullptr, "Ошибка!", "Урок с таким названием уже есть!");
            return;
        }
    }

    Lesson->SetName(name);

    bool flag = false;

    Teacher *chosenTeacher;

    for (int i = 0; i < Teachers->count() && !flag; i++)
    {
        Teacher* current = (Teacher*) Teachers->itemWidget(Teachers->item(i));

        flag = current->GetName() ==
                ui->TeacherList->currentText();

        if (flag)
            chosenTeacher = current;
    }

    Lesson->SetTeacher(chosenTeacher);

    Lesson->SetHowManyPerTwoWeeks(ui->AmountBox->value());

    this->close();
}

void ChangeLessonForm::on_DialogButtons_rejected()
{
    this->close();
}

