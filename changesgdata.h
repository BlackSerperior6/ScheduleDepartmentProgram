#ifndef CHANGESGDATA_H
#define CHANGESGDATA_H

#include <QDialog>

#include "studygroup.h"
#include <QListWidget>

namespace Ui {
class ChangeSgData;
}

class ChangeSgData : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeSgData(QWidget *parent = nullptr, StudyGroup *group = nullptr);
    ~ChangeSgData();

private slots:
    void on_Buttons_accepted();

    void on_Buttons_rejected();

private:
    Ui::ChangeSgData *ui;

    StudyGroup *Group;
};

#endif // CHANGESGDATA_H
