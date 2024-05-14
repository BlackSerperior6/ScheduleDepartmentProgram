#ifndef CHANGEWORKSLOT_H
#define CHANGEWORKSLOT_H

#include <QDialog>
#include <QListWidget>

#include "workslot.h"

namespace Ui {
class ChangeWorkSlot;
}

class ChangeWorkSlot : public QDialog //Форма для редактирования рабочего слота
{
    Q_OBJECT

public:
    explicit ChangeWorkSlot(QWidget *parent = nullptr, WorkSlot *slot = nullptr, QListWidget *parentlist = nullptr);
    ~ChangeWorkSlot();

private slots:
    void on_DialogButtons_accepted();

    void on_DialogButtons_rejected();

private:
    Ui::ChangeWorkSlot *ui;

    WorkSlot *Slot; //Сам слот

    QListWidget *Parentlist;
};

#endif // CHANGEWORKSLOT_H
