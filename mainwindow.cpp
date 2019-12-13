#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QValidator>
#include <map>
#include <vector>
#include "student.h"
#include <algorithm>

using namespace std;

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
    QRegExp regex_fio("([А-Я]{1}[а-я]+ [А-Я]{1}[а-я]+ [А-Я]{1}[а-я]+){45}$");
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
    if(current.get_can_pay())
        current.set_student_bill(ui->spin_bill->value());
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
    if(current.get_can_pay()){
        ui->spin_bill->setValue(current.get_student_bill());
        ui->spin_bill->setEnabled(true);
    }
    else{
        ui->spin_bill->setEnabled(false);
        ui->spin_bill->setValue(12000);
    }
}


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
void MainWindow::on_check_dogvor_clicked(){
    if(ui->check_dogvor->isChecked())
        ui->spin_bill->setEnabled(true);
    else{
        ui->spin_bill->setValue(12000);
        ui->spin_bill->setEnabled(false);
    }
}

//проверка на уникальность экзамена(bag - after clicked other element)
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
    if(ui->radio_math_one_2->isChecked()){
        //активировать ее родное введение
        ui->spin_math_2->setEnabled(true);

        ui->spin_rus_2->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
        ui->spin_math->setEnabled(false);
        ui->spin_math_3->setEnabled(false);
    }
    else{
        ui->spin_rus_2->setEnabled(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_math->setEnabled(true);
        ui->spin_math_3->setEnabled(true);
    }
}
void MainWindow::on_radio_math_one_3_clicked(){
    if(ui->radio_math_one_3->isChecked()){
        //активировать ее родное введение
        ui->spin_math_3->setEnabled(true);

        ui->spin_rus_3->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
        ui->spin_math_2->setEnabled(false);
        ui->spin_math->setEnabled(false);
    }
    else{
        ui->spin_rus_3->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_math->setEnabled(true);
    }
}
void MainWindow::on_radio_math_two_clicked(){
    if(ui->radio_math_two->isChecked()){
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
void MainWindow::on_radio_math_two_2_clicked(){
    if(ui->radio_math_two_2->isChecked()){
        //активировать ее родное введение
        ui->spin_math_2->setEnabled(true);

        ui->spin_rus_2->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
        ui->spin_math->setEnabled(false);
        ui->spin_math_3->setEnabled(false);
    }
    else{
        ui->spin_rus_2->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
        ui->spin_math->setEnabled(true);
        ui->spin_math_3->setEnabled(true);
    }
}
void MainWindow::on_radio_math_two_3_clicked(){
    if(ui->radio_math_two_3->isChecked()){
        //активировать ее родное введение
        ui->spin_math_3->setEnabled(true);

        ui->spin_rus_3->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
        ui->spin_math_2->setEnabled(false);
        ui->spin_math->setEnabled(false);
    }
    else{
        ui->spin_rus_3->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_math->setEnabled(true);
    }
}

void MainWindow::on_radio_phys_one_clicked(){
    if(ui->radio_phys_one->isChecked()){
        //активировать ее родное введение
        ui->spin_phis->setEnabled(true);

        ui->spin_rus->setEnabled(false);
        ui->spin_math->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
    }
    else{
        ui->spin_rus->setEnabled(true);
        ui->spin_math->setEnabled(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
    }
}
void MainWindow::on_radio_phys_one_2_clicked(){
    if(ui->radio_phys_one_2->isChecked()){
        //активировать ее родное введение
        ui->spin_phis_2->setEnabled(true);

        ui->spin_rus_2->setEnabled(false);
        ui->spin_math_2->setEnabled(false);
        ui->spin_phis->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
    }
    else{
        ui->spin_rus_2->setEnabled(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_phis->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
    }
}
void MainWindow::on_radio_phys_one_3_clicked(){
    if(ui->radio_phys_one_3->isChecked()){
        //активировать ее родное введение
        ui->spin_phis_3->setEnabled(true);

        ui->spin_rus_3->setEnabled(false);
        ui->spin_math_3->setEnabled(false);
        ui->spin_phis->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
    }
    else{
        ui->spin_rus_3->setEnabled(true);
        ui->spin_math_3->setEnabled(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_phis->setEnabled(true);
    }
}

void MainWindow::on_radio_phys_two_clicked(){
    if(ui->radio_phys_two->isChecked()){
        //активировать ее родное введение
        ui->spin_phis->setEnabled(true);

        ui->spin_rus->setEnabled(false);
        ui->spin_math->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
    }
    else{
        ui->spin_rus->setEnabled(true);
        ui->spin_math->setEnabled(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
    }
}
void MainWindow::on_radio_phys_two_2_clicked(){
    if(ui->radio_phys_two_2->isChecked()){
        //активировать ее родное введение
        ui->spin_phis_2->setEnabled(true);

        ui->spin_rus_2->setEnabled(false);
        ui->spin_math_2->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
        ui->spin_phis->setEnabled(false);
    }
    else{
        ui->spin_rus_2->setEnabled(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_phis->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
    }
}
void MainWindow::on_radio_phys_3_clicked(){
    if(ui->radio_phys_3->isChecked()){
        //активировать ее родное введение
        ui->spin_phis_3->setEnabled(true);

        ui->spin_rus_3->setEnabled(false);
        ui->spin_math_3->setEnabled(false);
        ui->spin_phis->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
    }
    else{
        ui->spin_rus_3->setEnabled(true);
        ui->spin_math_3->setEnabled(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_phis->setEnabled(true);
    }
}

void MainWindow::on_radio_rus_clicked(){
    if(ui->radio_rus->isChecked()){
        //активировать ее родное введение
        ui->spin_rus->setEnabled(true);

        ui->spin_rus_2->setEnabled(false);
        ui->spin_rus_3->setEnabled(false);
        ui->spin_math->setEnabled(false);
        ui->spin_phis->setEnabled(false);
    }
    else{
        ui->spin_rus_2->setEnabled(true);
        ui->spin_rus_3->setEnabled(true);
        ui->spin_math->setEnabled(true);
        ui->spin_phis->setEnabled(true);
    }
}
void MainWindow::on_radio_rus_2_clicked(){
    if(ui->radio_rus_2->isChecked()){
        //активировать ее родное введение
        ui->spin_rus_2->setEnabled(true);

        ui->spin_rus->setEnabled(false);
        ui->spin_rus_3->setEnabled(false);
        ui->spin_math_2->setEnabled(false);
        ui->spin_phis_2->setEnabled(false);
    }
    else{
        ui->spin_rus->setEnabled(true);
        ui->spin_rus_3->setEnabled(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_phis_2->setEnabled(true);
    }
}
void MainWindow::on_radio_rus_3_clicked(){
    if(ui->radio_rus_3->isChecked()){
        //активировать ее родное введение
        ui->spin_rus_3->setEnabled(true);

        ui->spin_rus->setEnabled(false);
        ui->spin_rus_2->setEnabled(false);
        ui->spin_math_3->setEnabled(false);
        ui->spin_phis_3->setEnabled(false);
    }
    else{
        ui->spin_rus->setEnabled(true);
        ui->spin_rus_2->setEnabled(true);
        ui->spin_math_3->setEnabled(true);
        ui->spin_phis_3->setEnabled(true);
    }
}

//для золотой или серебрянной медали и при первом экзе более 90 - автомат
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
void MainWindow::on_spin_math_valueChanged(){
    if(ui->check_medal->isChecked() && ui->spin_math->value() >= 90){
        ui->group_marks_exam_2->setEnabled(false);
        ui->group_marks_exam_3->setEnabled(false);
        ui->spin_rus->setValue(100);
        ui->spin_rus->setEnabled(false);
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
        ui->spin_rus->setEnabled(true);
        ui->spin_phis->setEnabled(true);

    }
}
void MainWindow::on_spin_phis_valueChanged(){
    if(ui->check_medal->isChecked() && ui->spin_phis->value() >= 90){
        ui->group_marks_exam_2->setEnabled(false);
        ui->group_marks_exam_3->setEnabled(false);
        ui->spin_rus->setValue(100);
        ui->spin_rus->setEnabled(false);
        ui->spin_math->setEnabled(false);
        ui->spin_math->setValue(100);
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

//работа с таблицей

//сохраниние и работа с таблицей
void MainWindow::on_btn_create_clicked(){
    Student student;
    save(student);
    int insert_pos = get_row(student);

    ui->table_students->insertRow(insert_pos);
    list_of_students.push_back(student);
    sort(list_of_students.begin(), list_of_students.end(), Student::compare_students);

    QTableWidgetItem *item;

    //Заполняем первую ячейку
    item = new QTableWidgetItem(list_of_students[insert_pos].get_FIO());
    ui->table_students->setItem(insert_pos, 0, item);
    ui->table_students->item(insert_pos,0)->setTextAlignment(Qt::AlignCenter);

    //Заполняем вторую ячейку
    item = new QTableWidgetItem(list_of_students[insert_pos].get_birthday().toString());
    ui->table_students->setItem(insert_pos, 1, item);
    ui->table_students->item(insert_pos,1)->setTextAlignment(Qt::AlignCenter);

    //Заполняем третью ячейку
    item = new QTableWidgetItem(list_of_students[insert_pos].get_middle_score());
    ui->table_students->setItem(insert_pos, 2, item);
    ui->table_students->item(insert_pos,2)->setTextAlignment(Qt::AlignCenter);

    ui->btn_save->setEnabled(true);
    ui->btn_delete->setEnabled(true);
}
void MainWindow::on_btn_save_clicked(){
     on_btn_delete_clicked(); on_btn_create_clicked();
}
void MainWindow::on_btn_delete_clicked(){
    int current_row = ui->table_students->currentRow();
    ui->table_students->removeRow(current_row);
    list_of_students.erase(list_of_students.begin() + current_row);

    if(list_of_students.empty()){
        ui->btn_save->setEnabled(false);
        ui->btn_delete->setEnabled(false);
    }

    if(current_row == -1)
        clear_fields();
}
void MainWindow::on_btn_fill_clicked(){}
void MainWindow::on_table_student_cellClicked(){
    clear_fields();
    if(!list_of_students.empty()){
        int row = ui->table_students->currentRow();
        show_student(list_of_students[row]);
    }
}
void MainWindow::clear_fields(){
    Student student = Student();
    show_student(student);
}
int MainWindow::get_row(Student student){
    int index = 0;
    while(!list_of_students.empty() && Student::compare_students(student, list_of_students[index])) index++;
    return index;
}
