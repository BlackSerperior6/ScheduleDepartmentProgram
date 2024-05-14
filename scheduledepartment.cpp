#include "scheduledepartment.h"
#include "ui_scheduledepartment.h"

#include <fstream>

#include <QMessageBox>
#include <QFileDialog>
#include <QTextCodec>

#include "studygroup.h"
#include "teacher.h"
#include "changesgdata.h"
#include "changeteacherfrom.h"

ScheduleDepartment::ScheduleDepartment(QWidget *parent) //Инициализация интерфейса
    : QMainWindow(parent)
    , ui(new Ui::ScheduleDepartment)
{
    ui->setupUi(this);

    //Установка русской кодовой страницы
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP 1251")); //setlocale(LC_ALL, RUS)

    //Инициализация нужных переменных
    StudentGroupsRowSelected = -1; //Выбранный ряд в списке учеников
    TeachersGroupsRowSelected = -1; //В списке учителей

    FilePath = ""; //Путь к папке, в которую будут отправлены файлы
}

ScheduleDepartment::~ScheduleDepartment()
{
    delete ui;
}

void ScheduleDepartment::on_AddStudyGroupButton_clicked()
{
    if (ui->TeacherList->count() == 0) //Нельзя добавить группу, если нет учителя
    {
        QMessageBox::information(nullptr, "Ошибка!",
                                 "Перед добавление группы добавьте хотя бы одного учителя");
        return;
    }

    //Инициализация нового ученика
    QListWidgetItem *item = new QListWidgetItem;
    StudyGroup *group = new StudyGroup(nullptr, ui->TeacherList, ui->StudyGroupList);

    //Если пользователь отменил создание
    if (group->GetName().isEmpty() || group->GetLessons()->count() == 0)
    {
        //Чистка памяти
        delete item;
        delete group;
        return;
    }

    //Добавляем новую группу
    ui->StudyGroupList->addItem(item);
    ui->StudyGroupList->setItemWidget(item, group);
}

void ScheduleDepartment::on_RemoveStudyGroupButton_clicked()
{
    if (StudentGroupsRowSelected == -1) //Ничего не делаем, если не выбран ряд
        return;

    //Удаление выбраного элемента
    QListWidgetItem *it = ui->StudyGroupList->takeItem(StudentGroupsRowSelected);
    delete it;

    ui->StudyGroupList->setCurrentRow(-1); //Установка выбранного ряда на "ничего не выбрано"
}

void ScheduleDepartment::on_StudyGroupList_currentRowChanged(int currentRow)
{
    StudentGroupsRowSelected = currentRow;
}

void ScheduleDepartment::on_ClearSudyGroupButton_clicked()
{
    ui->StudyGroupList->clear();
}

void ScheduleDepartment::on_StudyGroupList_itemDoubleClicked(QListWidgetItem *item) //Метод редактирования группы
{
    StudyGroup *group =  (StudyGroup*) ui->StudyGroupList->itemWidget(item); //Получаем группу

    //Вызываем интерфейс для редактирования группы
    ChangeSgData *win = new ChangeSgData(nullptr, group, ui->TeacherList, ui->StudyGroupList);

    win->setModal(true);
    win->exec();
}

void ScheduleDepartment::on_AddTeacherButton_clicked()
{
    //Иницализирием нового педагока
    QListWidgetItem *item = new QListWidgetItem;
    Teacher *teach = new Teacher(nullptr, ui->TeacherList);

    //Если его создание было отменено
    if (teach->GetName().isEmpty() || teach->GetWorkSlots()->count() == 0)
    {
        //Чистим память
        delete teach;
        delete item;
        return;
    }

    //Добавляем в список
    ui->TeacherList->addItem(item);
    ui->TeacherList->setItemWidget(item, teach);
}

void ScheduleDepartment::on_TeacherList_currentRowChanged(int currentRow)
{
    TeachersGroupsRowSelected = currentRow;
}

void ScheduleDepartment::on_RemoveTeacherButton_clicked()
{
    if (TeachersGroupsRowSelected == -1) //Ничего не делаем, если никто не выбран
        return;

    bool flag = false;

    //Проверка на то, не преподает ли преподователь в какой - либо группе
    for (int i = 0; i < ui->StudyGroupList->count() && !flag; i++)
    {
        StudyGroup* group = (StudyGroup*)
                ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));

        for (int j = 0; j < group->GetLessons()->count() && !flag; j++)
        {
            Lessons* current = (Lessons*) group->GetLessons()->
                    itemWidget(group->GetLessons()->item(j));

            flag = ((Teacher*) current->GetTeacher())->GetName() ==
                    ((Teacher*)
                     ui->TeacherList->
                     itemWidget(ui->TeacherList->item(TeachersGroupsRowSelected)))->GetName();

            if (flag) //Если преподает, выводим сообщение о ошибке и запрещаем удаление
                QMessageBox::information(nullptr, "Ошибка",
                                         "Данный предодователь преподает в группе "
                                         + group->GetName() + ", невозможно удаление!");
        }
    }

    if (flag) //Запрещаем удаление, если преподает
        return;

    //Удаляем элемент
    QListWidgetItem *it = ui->TeacherList->takeItem(TeachersGroupsRowSelected);
    delete it;

    ui->TeacherList->setCurrentRow(-1);
}

void ScheduleDepartment::on_TeacherList_itemDoubleClicked(QListWidgetItem *item) //Редактирования учителей
{
    //Берем преподователя
    Teacher *teach =  (Teacher*) ui->TeacherList->itemWidget(item);

    //Вызываем интерфейс для его редактирования
    ChangeTeacherFrom *win = new ChangeTeacherFrom(nullptr, teach, ui->TeacherList);

    win->setModal(true);
    win->exec();
}


void ScheduleDepartment::on_GenerateScheduelButton_clicked() //Генерация рассписания
{
    if (FilePath == "") //Выводим сообщение о ошибке, если не указан путь к папке
    {
        QMessageBox::information(nullptr, "Ошибка!", "Вы не указали папку, в которую надо вывести рассписание!");
        return;
    }
    else if (!QDir(FilePath).exists()) //Доп. проверка на то, что папка все еще существует
    {
        //Если не существует, то:

        //1. Выводим сообщение о ошибке
        QMessageBox::information(nullptr, "Ошибка!", "Что то случилось с выходной папкой. Укажите новую!");

        //2. Возвращаем надпись о том, что папка не указана
        ui->NoPathLable->setText("Не указан путь к папке для выходного продукта!");

        //3. Очищаем путь
        FilePath = "";

        return;
    }

    if (ui->TeacherList->count() == 0) //Без учителей нет рассписания
    {
        QMessageBox::information(nullptr, "Ошибка!", "Вы не указали ни одного преподователя");
        return;
    }

    if (ui->StudyGroupList->count() == 0) //Без групп нет рассписания
    {
        QMessageBox::information(nullptr, "Ошибка!", "Вы не указали ни одной группы");
        return;
    }

    bool mainFlag = true; //true - пока рассписание составлять можно

    for (int i = 0; i < ui->StudyGroupList->count() && mainFlag; i++) //Проходим по всем группам
    {
        StudyGroup *currentSg = (StudyGroup*)
                ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));

        for (int j = 0; j < currentSg->GetLessons()->count() && mainFlag; j++) //Проходим по всем её предметам
        {
            Lessons* currentLesson = (Lessons*)
                    currentSg->GetLessons()->itemWidget(currentSg->GetLessons()->item(j));

            for (int k = 0; k < currentLesson->GetHowManyPerTwoWeeks() && mainFlag; k++) //Добавляем сколько надо раз в рассписание
            {
                Teacher* currentTeacher = (Teacher*) currentLesson->GetTeacher(); //Берем преподователя, который должен вести урок

                bool subFlag = false; //Получилось найти место под урок

                //Ищем подходящие время
                for (int p = 0; p < currentTeacher->GetWorkSlots()->count() && !subFlag; p++)
                {
                    WorkSlot* currentWorkSlot = (WorkSlot*)
                            currentTeacher->GetWorkSlots()
                            ->itemWidget(currentTeacher->GetWorkSlots()->item(p));

                    ParsedWorkSlot slot = currentWorkSlot->ParseToIndexes(); //Переводим время в индексы массива

                    //true - у группы свободно время с учетом того, учится ли группа в субботу
                    bool NoProblemWithTheGroup = currentSg->GetScheduel()[slot.DayIndex]
                            [slot.TimeIndex][slot.WeekIndex] == nullptr &&
                            (slot.DayIndex != 5 || currentSg->IsStudyingAtSaturdays());

                    if (currentTeacher->GetScheduel()[slot.DayIndex]
                            [slot.TimeIndex][slot.WeekIndex]
                            == nullptr && NoProblemWithTheGroup) //Если у учителя также все свободно
                    {
                        //Вставляем пару в рассписание группы и учителя

                        currentTeacher->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex] = currentLesson;

                        currentSg->GetScheduel()[slot.DayIndex]
                                [slot.TimeIndex][slot.WeekIndex] = currentLesson;

                        subFlag = true;
                    }
                }

                //Если не вышло поставить урок циклом выше

                if (!subFlag)
                {
                    //Вновь пытаемся найти время, путем перестановки предмета другого педагога
                    for (int p = 0; p < currentTeacher->GetWorkSlots()->count() && !subFlag; p++)
                    {
                        ParsedWorkSlot slot = ((WorkSlot*)  //Время текущего учителя, на это место хоти поставить пару
                                               currentTeacher->GetWorkSlots()
                                               ->itemWidget(currentTeacher->GetWorkSlots()->item(p)))->ParseToIndexes();

                        //Проверка субботы и то, что учитель в этом время свободен
                        if ((slot.DayIndex == 5 && !currentSg->IsStudyingAtSaturdays()) ||
                                currentTeacher->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex] != nullptr)
                            continue;

                        //Берем учителя, который занял это время у группы
                        Teacher *checking = (Teacher*) currentSg->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex]
                                ->GetTeacher();

                        //Пытаемся передвинуть пару на другое время
                        for (int a = 0; a < checking->GetWorkSlots()->count() && !subFlag; a++)
                        {
                            ParsedWorkSlot subSlot = ((WorkSlot*) //Время другого педагога, чью пару пытаемся сдвинуть
                                                      checking->GetWorkSlots()
                                                      ->itemWidget(checking->GetWorkSlots()->item(a)))->ParseToIndexes();

                            //Если время свободно и у учителя (пару которого пытаемся сдвинуть) и у группы
                            if (currentSg->GetScheduel()[subSlot.DayIndex][subSlot.TimeIndex][subSlot.WeekIndex] == nullptr &&
                                    checking->GetScheduel()[subSlot.DayIndex][subSlot.TimeIndex][subSlot.WeekIndex] == nullptr)
                            {
                                //Меняем местами пары в группе

                                currentSg->GetScheduel()[subSlot.DayIndex][subSlot.TimeIndex][subSlot.WeekIndex] =
                                checking->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex];

                                currentSg->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex] = currentLesson;

                                currentTeacher->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex] = currentLesson;;

                                checking->GetScheduel()[subSlot.DayIndex][subSlot.TimeIndex][subSlot.WeekIndex] =
                                        checking->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex];

                                checking->GetScheduel()[slot.DayIndex][slot.TimeIndex][slot.WeekIndex] = nullptr;

                                subFlag = true;
                            }
                        }
                    }
                }

                mainFlag = subFlag;
            }
        }
    }

    //Если не получилось составить рассписание, то мы выводим сообщение о ошибке, но все равно создаем файлы с тем, что получилось поставить

    if (!mainFlag)
        QMessageBox::information(nullptr, "Ошибка!",
                                 "Не получилось полностью сгенерировать рассписание. Генериуем файлы с тем, что удалось поставить");


    for (int i = 0; i < ui->StudyGroupList->count(); i++)
    {
        StudyGroup* current = (StudyGroup*) ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i));

        //Создаем файл с названием группы
        std::ofstream stream(FilePath.toStdString() +  "/" + current->GetName().toLocal8Bit().data()
                             + ".txt");

        //Вводим в него офформление
        for (int j = 0; j < 6; j++)
        {
            switch (j)
            {
            case 0:
                stream << "Понедельник:";
                break;
            case 1:
                stream << "Вторник:";
                break;
            case 2:
                stream << "Среда:";
                break;
            case 3:
                stream << "Четверг:";
                break;
            case 4:
                stream << "Пятница:";
                break;
            case 5:
                stream << "Суббота:";
                break;
            }

            stream << "\n";

            for (int k = 0; k < 6; k++)
            {
                stream << "  ";

                switch (k)
                {
                case 0:
                    stream << "8:00:";
                    break;
                case 1:
                    stream << "9:40:";
                    break;
                case 2:
                    stream << "11:30";
                    break;
                case 3:
                    stream << "13:20:";
                    break;
                case 4:
                    stream << "15:00";
                    break;
                case 5:
                    stream << "16:40";
                    break;
                }

                stream << "\n";

                for (int u = 0; u < 2; u++)
                {
                    stream << "         ";

                    switch (u)
                    {
                    case 0:
                        stream << "1-ая неделя:";
                        break;
                    case 1:
                        stream << "2-ая неделя:";
                        break;
                    }

                    //Если в это время у группы что - то есть, то вписываем в файл название предмета и педагога
                    if (current->GetScheduel()[j][k][u] != nullptr)
                        stream << "  " +  current->GetScheduel()[j][k][u]->GetName().toStdString() +
                                  "  " + "(" + ((Teacher*) current->GetScheduel()[j][k][u]->GetTeacher())->GetName()
                                  .toStdString() + ")";

                    stream << "\n";
                }
            }

            stream << "\n\n\n";
        }

        stream.close(); //Закрываем файл
    }

    //Проделываем тоже самое с учителями
    for (int i = 0; i < ui->TeacherList->count(); i++)
    {
        Teacher* current = (Teacher*) ui->TeacherList->itemWidget(ui->TeacherList->item(i));

        std::ofstream stream(FilePath.toStdString() +  "/" + current->GetName().toLocal8Bit().data()
                             + ".txt");

        for (int j = 0; j < 6; j++)
        {
            switch (j)
            {
            case 0:
                stream << "Понедельник:";
                break;
            case 1:
                stream << "Вторник:";
                break;
            case 2:
                stream << "Среда:";
                break;
            case 3:
                stream << "Четверг:";
                break;
            case 4:
                stream << "Пятница:";
                break;
            case 5:
                stream << "Суббота:";
                break;
            }

            stream << "\n";

            for (int k = 0; k < 6; k++)
            {
                stream << "  ";

                switch (k)
                {
                case 0:
                    stream << "8:00:";
                    break;
                case 1:
                    stream << "9:40:";
                    break;
                case 2:
                    stream << "11:30";
                    break;
                case 3:
                    stream << "13:20:";
                    break;
                case 4:
                    stream << "15:00";
                    break;
                case 5:
                    stream << "16:40";
                    break;
                }

                stream << "\n";

                for (int u = 0; u < 2; u++)
                {
                    stream << "         ";

                    switch (u)
                    {
                    case 0:
                        stream << "1-ая неделя:";
                        break;
                    case 1:
                        stream << "2-ая неделя:";
                        break;
                    }

                    if (current->GetScheduel()[j][k][u] != nullptr)
                        stream << " " << current->GetScheduel()[j][k][u]->GetName().toStdString();

                    stream << "\n";
                }
            }

            stream << "\n\n\n";
        }

        stream.close();
    }

    //Сообщение о успехе
    if (mainFlag)
        QMessageBox::information(nullptr, "Ура!", "Рассписание для всех групп и учителей было"
                                                  " успешно создано!");


    //Чистка рассписаний для дальнейших генераций
    for (int i = 0; i < ui->StudyGroupList->count() ; i++)
        ((StudyGroup*) ui->StudyGroupList->itemWidget(ui->StudyGroupList->item(i)))->ClearScheduel();

    for (int i = 0; i < ui->TeacherList->count(); i++)
        ((Teacher*) ui->TeacherList->itemWidget(ui->TeacherList->item(i)))->ClearScheduel();
}


void ScheduleDepartment::on_ChooseFolderButton_clicked()
{
    //Получаем путь
    QString path = QFileDialog::getExistingDirectory();

    //Ничего не делаем, если путь пустой
    if (path == "")
        return;

    //Задаем путь
    FilePath = path;
    ui->NoPathLable->setText("");
}
