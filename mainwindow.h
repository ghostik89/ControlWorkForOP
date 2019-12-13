#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include <vector>

using namespace std;

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
    vector<Student> list_of_students;


    void save(Student& current);
    void show_student(Student current);
    void clear_fields();
    int get_row(Student);

private slots:
    void on_check_medal_clicked();
    void on_check_dogvor_clicked();

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
    void on_spin_math_valueChanged();
    void on_spin_phis_valueChanged();

    //сохраниние и работа с таблицей
    void on_btn_create_clicked();
    void on_btn_save_clicked();
    void on_btn_delete_clicked();
    void on_btn_fill_clicked();
    void on_table_student_cellClicked();
};

#endif // MAINWINDOW_H
