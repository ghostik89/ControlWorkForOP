#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"

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
    Student first_student = Student();//первый студент
    Student second_student = Student();//второй студент

    void save(Student& current);
    void show_student(Student current);

private slots:
    void on_btn_save_first_student_clicked();
    void on_btn_save_second_student_clicked();
    void on_btn_first_student_clicked();
    void on_btn_second_student_clicked();
    void on_check_medal_clicked();

    //проверка уникальности экзамена
    void on_radio_math_one_clicked();
    void on_radio_math_one_2_clicked();
    void on_radio_math_one_3_clicked();

    void on_radio_math_two_clicked();
    void on_radio_math_two_2_clicked();
    void on_radio_math_two_3_clicked();

    void on_radio_phys_one_clicked();
    void on_radio_phys_one_2_clicked();
    void on_radio_phys_one_3_clicked();

    void on_radio_phys_two_clicked();
    void on_radio_phys_two_2_clicked();
    void on_radio_phys_3_clicked();

    void on_radio_rus_clicked();
    void on_radio_rus_2_clicked();
    void on_radio_rus_3_clicked();

    //автомат
    void on_spin_rus_valueChanged();
};

#endif // MAINWINDOW_H
