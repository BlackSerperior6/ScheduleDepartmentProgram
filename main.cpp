#include "scheduledepartment.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScheduleDepartment w;
    w.show();
    return a.exec();
}
