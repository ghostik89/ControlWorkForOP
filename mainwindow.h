#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include "examplevalidator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Student first_student;//первый студент
    Student second_student;//второй студент
    ExampleValidator valid;

private slots:
    //слоты для записи и хранения студентов
    void slt_save_first_student();
    void slt_save_second_student();
    void slt_show_first_student();
    void slt_show_second_student();

    void slt_medal_flag(bool);//бесполезная хня
    void slt_middle_marks(bool);//проверка средней оценки с учетом медали
    void slt_marks_tabs();//проверка балла экзамена с учетом экзамена(не правильно подключен слот)
    void slt_check_unquie_exam();//проверка на уникальность экзамена
    void slt_gold_medal_exam(bool);//бесполезно
    //проверка даты рождения
    //проверка ФИО
    //заблокировать все остальные поля ввода, если введен один из экзаменов
};

#endif // MAINWINDOW_H
