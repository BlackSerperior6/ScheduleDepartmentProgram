#include "scheduledepartment.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    system("chcp 1251");
    QApplication a(argc, argv);
    ScheduleDepartment w;
    w.show();
    return a.exec();
}
