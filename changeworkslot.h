#ifndef CHANGEWORKSLOT_H
#define CHANGEWORKSLOT_H

#include <QDialog>

#include "workslot.h"

#include <QListWidget>

namespace Ui {
class ChangeWorkSlot;
}

class ChangeWorkSlot : public QDialog
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

    WorkSlot *Slot;

    QListWidget *Parentlist;
};

#endif // CHANGEWORKSLOT_H
