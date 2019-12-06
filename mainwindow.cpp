#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QValidator>
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //задание верной даты
    ui->student_birthday->setMaximumDate(QDate(QDate::currentDate().year() - 15, QDate::currentDate().month(), QDate::currentDate().day()));
    ui->student_birthday->setMinimumDate(QDate(QDate::currentDate().year() - 50, QDate::currentDate().month(), QDate::currentDate().day()));
    ui->student_birthday->setDate(QDate(QDate::currentDate().year() - 15, QDate::currentDate().month(), QDate::currentDate().day()));

    //задание валидатора для ФИО
    QRegExp regex_fio("[А-Я]{1}[а-я]+ [А-Я]{1}[а-я]+ [А-Я]{1}[а-я]+$");
    QValidator *fio_validate = new QRegExpValidator(regex_fio, this);
    ui->line_full_name->setValidator(fio_validate);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::save(Student& current){
    current.set_FIO(ui->line_full_name->text());
    current.set_medal(ui->check_medal->isChecked());
    current.set_gender(ui->radio_man->isChecked() ? "Мужской": "Женский");
    current.set_can_pay(ui->check_dogvor->isChecked());
    current.set_birthday(ui->student_birthday->date().toString());

    //получить язык
    if(ui->radio_lang_french->isChecked())
        current.set_language("Французкий");
    if(ui->radio_lang_english->isChecked())
        current.set_language("Английский");
    if(ui->radio_lang_german->isChecked())
        current.set_language("Немецкий");
    if(ui->radio_lang_korean->isChecked())
        current.set_language("Корейский");
    if(ui->radio_lang_chinise->isChecked())
        current.set_language("Китайский");
    if(ui->radio_lang_japanise->isChecked())
        current.set_language("Японский");

    current.set_middle_mark(ui->spin_middle_mark->value());


    //получить значения экзаменов
    if(ui->radio_rus->isChecked())
        current.set_first_exam("Русский", ui->spin_rus->value());
    if(ui->radio_math_one->isChecked())
        current.set_first_exam("Математика I", ui->spin_math->value());
    if(ui->radio_math_two->isChecked())
        current.set_first_exam("Математика II", ui->spin_math->value());
    if(ui->radio_phys_one->isChecked())
        current.set_first_exam("Физика I", ui->spin_phis->value());
    if(ui->radio_phys_two->isChecked())
        current.set_first_exam("Физика II", ui->spin_phis->value());

    if(ui->radio_rus_2->isChecked())
        current.set_second_exam("Русский", ui->spin_rus_2->value());
    if(ui->radio_math_one_2->isChecked())
        current.set_second_exam("Математика I", ui->spin_math_2->value());
    if(ui->radio_math_two_2->isChecked())
        current.set_second_exam("Математика II", ui->spin_math_2->value());
    if(ui->radio_phys_one_2->isChecked())
        current.set_second_exam("Физика I", ui->spin_phis_2->value());
    if(ui->radio_phys_two_2->isChecked())
        current.set_second_exam("Физика II", ui->spin_phis_2->value());

    if(ui->radio_rus_3->isChecked())
        current.set_third_exam("Русский", ui->spin_rus_3->value());
    if(ui->radio_math_one_3->isChecked())
        current.set_third_exam("Математика I", ui->spin_math_3->value());
    if(ui->radio_math_two_3->isChecked())
        current.set_third_exam("Математика II", ui->spin_math_3->value());
    if(ui->radio_phys_one_3->isChecked())
        current.set_third_exam("Физика I", ui->spin_phis_3->value());
    if(ui->radio_phys_3->isChecked())
        current.set_third_exam("Физика II", ui->spin_phis_3->value());

    current.set_can_pay(ui->check_dogvor->isChecked());
}
void MainWindow::show_student(Student current){
    ui->line_full_name->setText(current.get_FIO());
    ui->radio_man->setChecked(current.get_gender());
    ui->radio_woman->setChecked(!current.get_gender());
    ui->student_birthday->setDate(current.get_birthday());
    ui->check_medal->setChecked(current.get_medal());
    ui->spin_middle_mark->setValue(current.get_middle_mark());

    ui->radio_lang_english->setChecked(current.get_language() == "Английский");
    ui->radio_lang_german->setChecked(current.get_language() == "Немецкий");
    ui->radio_lang_french->setChecked(current.get_language() == "Французкий");
    ui->radio_lang_korean->setChecked(current.get_language() == "Корейский");
    ui->radio_lang_chinise->setChecked(current.get_language() == "Китайский");
    ui->radio_lang_japanise->setChecked(current.get_language() == "Японский");

    std::pair<QString, QString> temp;
    current.get_first_exam(temp);
    if(temp.first == "Русский"){
        ui->radio_rus->setChecked(true);
        ui->spin_rus->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика I"){
        ui->radio_math_one->setChecked(true);
        ui->spin_math->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика II"){
        ui->radio_math_two->setChecked(true);
        ui->spin_math->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика I"){
        ui->radio_phys_one->setChecked(true);
        ui->spin_phis->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика II"){
        ui->radio_phys_two->setChecked(true);
        ui->spin_phis->setValue(temp.second.toInt());
    }

    current.get_second_exam(temp);
    if(temp.first == "Русский"){
        ui->radio_rus_2->setChecked(true);
        ui->spin_rus_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика I"){
        ui->radio_math_one_2->setChecked(true);
        ui->spin_math_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика II"){
        ui->radio_math_two_2->setChecked(true);
        ui->spin_math_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика I"){
        ui->radio_phys_one_2->setChecked(true);
        ui->spin_phis_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика II"){
        ui->radio_phys_two_2->setChecked(true);
        ui->spin_phis_2->setValue(temp.second.toInt());
    }

    current.get_third_exam(temp);
    if(temp.first == "Русский"){
        ui->radio_rus_3->setChecked(true);
        ui->spin_rus_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика I"){
        ui->radio_math_one_3->setChecked(true);
        ui->spin_math_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика II"){
        ui->radio_math_two_3->setChecked(true);
        ui->spin_math_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика I"){
        ui->radio_phys_one_3->setChecked(true);
        ui->spin_phis_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика II"){
        ui->radio_phys_3->setChecked(true);
        ui->spin_phis_3->setValue(temp.second.toInt());
    }

    ui->check_dogvor->setChecked(current.get_can_pay());
}


void MainWindow::on_btn_save_first_student_clicked(){ MainWindow::save(first_student); }
void MainWindow::on_btn_save_second_student_clicked(){ MainWindow::save(second_student); }
void MainWindow::on_btn_first_student_clicked(){ MainWindow::show_student(first_student); }
void MainWindow::on_btn_second_student_clicked(){ MainWindow::show_student(second_student); }
void MainWindow::on_check_medal_clicked(){
    if(ui->check_medal->isChecked()){
        ui->spin_middle_mark->setValue(4.6);
        ui->spin_middle_mark->setMinimum(4.6);
        ui->spin_middle_mark->setMaximum(5.0);
    }
    else{
        ui->spin_middle_mark->setValue(3.0);
        ui->spin_middle_mark->setMinimum(3.0);
        ui->spin_middle_mark->setMaximum(4.5);
    }
}

//проверка на уникальность экзамена
void MainWindow::on_radio_math_one_clicked(){
    if(ui->radio_math_one->isChecked()){
        //активировать ее родное введение
        ui->spin_math->setEnabled(true);

        ui->spin_rus->setEnabled(false);
        ui->spin_phis->setEnabled(false);
        ui->spin_math_2->setEnabled(false);
        ui->spin_math_3->setEnabled(false);
    }
    else{
        ui->spin_rus->setEnabled(true);
        ui->spin_phis->setEnabled(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_math_3->setEnabled(true);
    }
}

void MainWindow::on_radio_math_one_2_clicked(){

}
void MainWindow::on_radio_math_one_3_clicked(){

}
void MainWindow::on_radio_math_two_clicked(){

}
void MainWindow::on_radio_math_two_2_clicked(){

}
void MainWindow::on_radio_math_two_3_clicked(){

}

void MainWindow::on_radio_phys_one_clicked(){}
void MainWindow::on_radio_phys_one_2_clicked(){}
void MainWindow::on_radio_phys_one_3_clicked(){}

void MainWindow::on_radio_phys_two_clicked(){}
void MainWindow::on_radio_phys_two_2_clicked(){}
void MainWindow::on_radio_phys_3_clicked(){}

void MainWindow::on_radio_rus_clicked(){}
void MainWindow::on_radio_rus_2_clicked(){}
void MainWindow::on_radio_rus_3_clicked(){}

void MainWindow::on_spin_rus_valueChanged(){
    if(ui->check_medal->isChecked() && ui->spin_rus->value() >= 90){
        ui->group_marks_exam_2->setEnabled(false);
        ui->group_marks_exam_3->setEnabled(false);
        ui->spin_math->setValue(100);
        ui->spin_math->setEnabled(false);
        ui->spin_phis->setEnabled(false);
        ui->spin_phis->setValue(100);
        ui->spin_rus_2->setValue(100);
        ui->spin_math_2->setValue(100);
        ui->spin_phis_2->setValue(100);
        ui->spin_rus_3->setValue(100);
        ui->spin_math_3->setValue(100);
        ui->spin_phis_3->setValue(100);
    }
    else{
        ui->group_marks_exam_2->setEnabled(true);
        ui->group_marks_exam_3->setEnabled(true);
        ui->spin_math->setEnabled(true);
        ui->spin_phis->setEnabled(true);

    }

}
