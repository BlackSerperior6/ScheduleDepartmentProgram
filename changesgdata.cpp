#include "changesgdata.h"
#include "ui_changesgdata.h"
#include <QMessageBox>

ChangeSgData::ChangeSgData(QWidget *parent, StudyGroup *group) :
    QDialog(parent),
    ui(new Ui::ChangeSgData)
{
    ui->setupUi(this);

    Group = group;
    ui->NameEdit->setText(group->GetName());
    ui->ScheduelEdit->setText(group->GetScheduel());
}

ChangeSgData::~ChangeSgData()
{
    delete ui;
}

void ChangeSgData::on_Buttons_accepted()
{
    if (ui->NameEdit->text().isEmpty() || ui->ScheduelEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Ошибка!", "Одно из полей оказалось пустым");
        return;
    }

    Group->SetName(ui->NameEdit->text());
    Group->SetScheduel(ui->ScheduelEdit->text());

    this->close();
}


void ChangeSgData::on_Buttons_rejected()
{
    this->close();
}

