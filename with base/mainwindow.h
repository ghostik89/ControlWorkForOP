#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include <QMap>
#include <vector>
#include "database.h"

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
    DataBase db;//база данных
    QString file_name;//имя файла


    ///
    /// \brief save функция для сохранения значений из виджетов в запись
    /// \param current запись, в которую производится сохранение
    ///
    void save(Student& current);

    ///
    /// \brief show_student функция для показа текущей записи в виджетах
    /// \param current запись, которую необходимо показать
    ///
    void show_student(Student current);

    ///
    /// \brief clear_fields очистить виджеты от предыдущей записи
    ///
    void clear_fields();

    ///
    /// \brief create_row создание новой строчки в таблице с записями
    /// \param current запись
    /// \param pos позиция новой строчки
    ///
    void create_row(Student current, int pos);

    int get_row(Student);//рудимент от прошлой лабы

private slots:
    void on_check_medal_clicked();//смена диапозона при наличии золотой медали
    void on_check_dogvor_clicked();//показать поле с ценой обучения на платной основе
    //автомат
    void on_spin_rus_valueChanged();
    void on_spin_math_valueChanged();
    void on_spin_phis_valueChanged();
    void closeEvent(QCloseEvent * event);//здесь должна была быть перегрузка крестика(но ее нет)
    //сохраниние и работа с таблицей
    void on_btn_create_clicked();//создание записи
    void on_btn_save_clicked();//сохранение записи
    void on_btn_delete_clicked();//удаление записи
    void on_btn_fill_clicked();//заполнить несколькими записями
    void slt_show_active();//показать активную запись из таблицы

    //проверка на уникальность
    void on_radio_math_one_toggled(bool checked);
    void on_radio_math_two_toggled(bool checked);
    void on_radio_phys_one_toggled(bool checked);
    void on_radio_phys_two_toggled(bool checked);
    void on_radio_rus_toggled(bool checked);
    void on_radio_math_one_2_toggled(bool checked);
    void on_radio_math_two_2_toggled(bool checked);
    void on_radio_phys_one_2_toggled(bool checked);
    void on_radio_phys_two_2_toggled(bool checked);
    void on_radio_rus_2_toggled(bool checked);
    void on_radio_math_one_3_toggled(bool checked);
    void on_radio_math_two_3_toggled(bool checked);
    void on_radio_phys_one_3_toggled(bool checked);
    void on_radio_phys_3_toggled(bool checked);
    void on_radio_rus_3_toggled(bool checked);
    void on_check_dogvor_toggled(bool checked);

    void on_create_file_triggered();//создание файла
    void on_open_from_file_triggered();//открыть из файла
    void on_safe_to_file_triggered();//сохранить в файл
    void on_save_as_to_file_triggered();//сохранить как
};

#endif // MAINWINDOW_H
