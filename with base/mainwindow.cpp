#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QValidator>
#include "student.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QFileDialog>
#include <QMapIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //задание верной даты
    ui->student_birthday->setMaximumDate(QDate(QDate::currentDate().year() - 15, QDate::currentDate().month(), QDate::currentDate().day()));
    ui->student_birthday->setMinimumDate(QDate(QDate::currentDate().year() - 50, QDate::currentDate().month(), QDate::currentDate().day()));
    ui->student_birthday->setDate(QDate(QDate::currentDate().year() - 15, QDate::currentDate().month(), QDate::currentDate().day()));

    connect(ui->table_students, SIGNAL(cellClicked(int, int)), this, SLOT(slt_show_active()));

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
        ui->spin_rus->setEnabled(true);
    }
    if(temp.first == "Математика I"){
        ui->radio_math_one->setChecked(true);
        ui->spin_math->setValue(temp.second.toInt());
        ui->spin_math->setEnabled(true);
    }
    if(temp.first == "Математика II"){
        ui->radio_math_two->setChecked(true);
        ui->spin_math->setEnabled(true);
        ui->spin_math->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика I"){
        ui->radio_phys_one->setChecked(true);
        ui->spin_phis->setEnabled(true);
        ui->spin_phis->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика II"){
        ui->radio_phys_two->setChecked(true);
        ui->spin_phis->setEnabled(true);
        ui->spin_phis->setValue(temp.second.toInt());
    }

    current.get_second_exam(temp);
    if(temp.first == "Русский"){
        ui->radio_rus_2->setChecked(true);
        ui->spin_rus_2->setEnabled(true);
        ui->spin_rus_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика I"){
        ui->radio_math_one_2->setChecked(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_math_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика II"){
        ui->radio_math_two_2->setChecked(true);
        ui->spin_math_2->setEnabled(true);
        ui->spin_math_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика I"){
        ui->radio_phys_one_2->setChecked(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_phis_2->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика II"){
        ui->radio_phys_two_2->setChecked(true);
        ui->spin_phis_2->setEnabled(true);
        ui->spin_phis_2->setValue(temp.second.toInt());
    }

    current.get_third_exam(temp);
    if(temp.first == "Русский"){
        ui->radio_rus_3->setChecked(true);
        ui->spin_rus_3->setEnabled(true);
        ui->spin_rus_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика I"){
        ui->radio_math_one_3->setChecked(true);
        ui->spin_math_3->setEnabled(true);
        ui->spin_math_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Математика II"){
        ui->radio_math_two_3->setChecked(true);
        ui->spin_math_3->setEnabled(true);
        ui->spin_math_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика I"){
        ui->radio_phys_one_3->setChecked(true);
        ui->spin_phis_3->setEnabled(true);
        ui->spin_phis_3->setValue(temp.second.toInt());
    }
    if(temp.first == "Физика II"){
        ui->radio_phys_3->setChecked(true);
        ui->spin_phis_3->setEnabled(true);
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
    }
}

//работа с таблицей

//сохраниние и работа с таблицей
void MainWindow::on_btn_create_clicked(){
    Student student;
    save(student);
    int insert_pos = db.get_current_row(student);

    ui->table_students->insertRow(insert_pos);
    //list_of_students.insert(list_of_students.begin() + insert_pos, student);
    db.set_student(student, insert_pos);

    create_row(student, insert_pos);
    ui->btn_save->setEnabled(true);
    ui->btn_delete->setEnabled(true);
}
void MainWindow::on_btn_save_clicked(){
     on_btn_delete_clicked(); on_btn_create_clicked();
}
void MainWindow::on_btn_delete_clicked(){
    int current_row = ui->table_students->currentRow();
    ui->table_students->removeRow(current_row);
    //list_of_students.erase(list_of_students.begin() + current_row);
    db.delete_student(current_row);

    if(db.count() == 0){
        ui->btn_save->setEnabled(false);
        ui->btn_delete->setEnabled(false);
    }

    if(current_row == -1)
        clear_fields();
}
void MainWindow::on_btn_fill_clicked(){
    Student student("Ололоев Владимир", QDate(1998, 5, 12), "мужской");
    qDebug() << student.get_sbirthday();
    int pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Иванов Иван", QDate(1997, 4, 11), "мужской");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Синецкая Александра", QDate(2000, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Свиридова Анастасия", QDate(2001, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Лермонтов Михаил", QDate(1980, 5, 12), "мужской");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Петрова Дарья", QDate(1997, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Афанасьев Виктор", QDate(1998, 5, 12), "мужской");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Липова Лилия", QDate(2000, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Синецкий Александр", QDate(1997, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Капеланов Кирилл", QDate(1998, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);

    student = Student("Тарасов Тарас", QDate(1995, 5, 12), "женский");
    pos = db.get_current_row(student);
    ui->table_students->insertRow(pos);
    //list_of_students.insert(list_of_students.begin() + pos, student);
    db.set_student(student, pos);
    create_row(student, pos);
}

void MainWindow::slt_show_active(){
    clear_fields();
    if(db.count() != 0){
        int row = ui->table_students->currentRow();
        show_student(db.get_current_student(row));
    }
}

void MainWindow::clear_fields(){
    Student student = Student();
    ui->spin_rus->setValue(0);
    ui->spin_math->setValue(0);
    ui->spin_phis->setValue(0);

    ui->spin_rus_2->setValue(0);
    ui->spin_math_2->setValue(0);
    ui->spin_phis_2->setValue(0);

    ui->spin_rus_3->setValue(0);
    ui->spin_math_3->setValue(0);
    ui->spin_phis_3->setValue(0);
    show_student(student);
}

void MainWindow::create_row(Student current,int pos){
    ui->btn_save->setEnabled(true);
    ui->btn_delete->setEnabled(true);
    QTableWidgetItem *item;

    //Заполняем первую ячейку
    item = new QTableWidgetItem(current.get_FIO());
    ui->table_students->setItem(pos, 0, item);
    ui->table_students->item(pos,0)->setTextAlignment(Qt::AlignCenter);

    //Заполняем вторую ячейку
    qDebug() << current.get_birthday().toString();
    item = new QTableWidgetItem(current.get_sbirthday());
    ui->table_students->setItem(pos, 1, item);
    ui->table_students->item(pos,1)->setTextAlignment(Qt::AlignCenter);

    //Заполняем третью ячейку
    item = new QTableWidgetItem(current.get_middle_score());
    ui->table_students->setItem(pos, 2, item);
    ui->table_students->item(pos,2)->setTextAlignment(Qt::AlignCenter);
    ui->table_students->setCurrentItem(item);
}

void MainWindow::on_radio_math_one_toggled(bool checked){
    ui->spin_math->setEnabled(checked);
    if(!checked)
        ui->spin_math->setValue(0);
}
void MainWindow::on_radio_math_two_toggled(bool checked){
    ui->spin_math->setEnabled(checked);
    if(!checked)
        ui->spin_math->setValue(0);
}
void MainWindow::on_radio_phys_one_toggled(bool checked){
    ui->spin_phis->setEnabled(checked);
    if(!checked)
        ui->spin_phis->setValue(0);
}
void MainWindow::on_radio_phys_two_toggled(bool checked){
    ui->spin_phis->setEnabled(checked);
    if(!checked)
        ui->spin_phis->setValue(0);
}
void MainWindow::on_radio_rus_toggled(bool checked){
    ui->spin_rus->setEnabled(checked);
    if(!checked)
        ui->spin_rus->setValue(0);
}

void MainWindow::on_radio_math_one_2_toggled(bool checked){
    ui->spin_math_2->setEnabled(checked);
    if(!checked)
        ui->spin_math_2->setValue(0);
}
void MainWindow::on_radio_math_two_2_toggled(bool checked){
    ui->spin_math_2->setEnabled(checked);
    if(!checked)
        ui->spin_math_2->setValue(0);
}
void MainWindow::on_radio_phys_one_2_toggled(bool checked){
    ui->spin_phis_2->setEnabled(checked);
    if(!checked)
        ui->spin_phis_2->setValue(0);
}
void MainWindow::on_radio_phys_two_2_toggled(bool checked){
    ui->spin_phis_2->setEnabled(checked);
    if(!checked)
        ui->spin_phis_2->setValue(0);
}
void MainWindow::on_radio_rus_2_toggled(bool checked){
    ui->spin_rus_2->setEnabled(checked);
    if(!checked)
        ui->spin_rus_2->setValue(0);
}

void MainWindow::on_radio_math_one_3_toggled(bool checked){
    ui->spin_math_3->setEnabled(checked);
    if(!checked)
        ui->spin_math_3->setValue(0);
}
void MainWindow::on_radio_math_two_3_toggled(bool checked){
    ui->spin_math_3->setEnabled(checked);
    if(!checked)
        ui->spin_math_3->setValue(0);
}
void MainWindow::on_radio_phys_one_3_toggled(bool checked){
    ui->spin_phis_3->setEnabled(checked);
    if(!checked)
        ui->spin_phis_3->setValue(0);
}
void MainWindow::on_radio_phys_3_toggled(bool checked){
    ui->spin_phis_3->setEnabled(checked);
    if(!checked)
        ui->spin_phis_3->setValue(0);
}
void MainWindow::on_radio_rus_3_toggled(bool checked){
    ui->spin_rus_3->setEnabled(checked);
    if(!checked)
        ui->spin_rus_3->setValue(0);
}

void MainWindow::on_check_dogvor_toggled(bool checked){
    ui->spin_bill->setEnabled(checked);
}


void MainWindow::on_create_file_triggered(){
    //ui->table_students->clearContents();
    QTextCodec* c = QTextCodec::codecForLocale();//установить кодек для файла
    QString nfile_name = QFileDialog::getOpenFileName(this, c->toUnicode("Create file"), "/", c->toUnicode("Text file(*.txt)"));//получить имя строки

    if(!nfile_name.isEmpty()){//если имя файла получено
        file_name = nfile_name;//скопируем имя файла

        //создаем бд
        ui->btn_create->setEnabled(true);
        ui->btn_fill->setEnabled(true);
        db = DataBase();
    }
    else{//выводим сообщение об ошибке
        QMessageBox ask(QMessageBox::Question, "Ошибка!", "Имя файла или директории не найдено, попробуйте создать его еще раз»", { QMessageBox::Ok });
    }
}

//void MainWindow::closeEvent(QCloseEvent * event) - здесь должна быть перегрузка закрытия
//{
//QMessageBox ask(QMessageBox::Question, "РџСЂРµРґСѓРїСЂРµР¶РґРµРЅРёРµ", "РЎРѕС…СЂР°РЅРёС‚СЊ РёР·РјРµРЅРµРЅРёСЏ?", { QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel }, this);
//int pressed = -1;
//if (!records.isModified() || (pressed = ask.exec()) != QMessageBox::Cancel)
//{
//if (pressed == QMessageBox::Save)
//if (lastAdress.isEmpty())
//on_saveBaseAs_triggered();
//else
//{
//if (!records.save(lastAdress))
//{ //СЃРѕРѕР±С‰РµРЅРёРµ Рѕ РЅРµСѓРґР°С‡Рµ
//QMessageBox ask(QMessageBox::Question, "РћС€РёР±РєР°", "РќРµ СѓРґР°Р»РѕСЃСЊ СЃРѕС…СЂР°РЅРёС‚СЊ С„Р°Р№Р»", { QMessageBox::Ok });
//}
//}
//}
//else
//{
//event->ignore();
//}

//}
void MainWindow::closeEvent(QCloseEvent * event){

}

void MainWindow::on_open_from_file_triggered(){//баг - если в таблице были записи, он их не затрет
    //db.clear();
    //ui->table_students->clear();
    QTextCodec* c = QTextCodec::codecForLocale();//получить кодек
    //получить имя файла
    QString nfile_name = QFileDialog::getOpenFileName(this, c->toUnicode("Open file"), "/", c->toUnicode("Text file(*.txt)"));

    if(!nfile_name.isEmpty()){//если имя файоа не пусто
        file_name = nfile_name;//копируем имя нового файла
        bool com = db.load_from_file(file_name);//загружаем его в бд

        if(!com){//если что-то пошло не такЫ
            qDebug() << "Incorrect!!";
            QMessageBox ask(QMessageBox::Question, "Ошибка!", "Невозможно считать файл!", { QMessageBox::Ok });
        }
        else{//если все отлично
            for(int i = 0; i < db.count(); i++){//генерируем новую таблицу из текущей бд
                Student temp;
                temp = db.get_current_student(i);
                create_row(temp, i);
             }
        }
        ui->btn_fill->setEnabled(com);
        ui->btn_save->setEnabled(com);
        ui->btn_create->setEnabled(com);
        ui->btn_delete->setEnabled(com);
    }
    else//иначе - вывести соообщение об ошибке
        QMessageBox ask(QMessageBox::Question, "Ошибка!", "404 файл не найден!", { QMessageBox::Ok });
}

void MainWindow::on_safe_to_file_triggered(){
    if(!file_name.isEmpty())//если имя файла не пустое
        db.save_to_file(file_name);//просто пишем в файл
    else
        on_save_as_to_file_triggered();//сохраняем как
}

void MainWindow::on_save_as_to_file_triggered(){
    QTextCodec* c = QTextCodec::codecForLocale();//узнать кодек
    //узнать имя файла
    QString nfile_name = QFileDialog::getOpenFileName(this, c->toUnicode("Open file"), "/", c->toUnicode("Text file(*.txt)"));

    if(!nfile_name.isEmpty()){//если оно не пусто
        file_name = nfile_name;//новое имя файла - копировать
        bool complete = db.save_to_file(file_name);//сохранить бд в файл
        if(!complete){//если что-то идет не так
            qDebug() << "Incorrect!!";
            //вывести сообщениеы
            QMessageBox ask(QMessageBox::Question, "Ошибка!", "Невозможно считать файл!", { QMessageBox::Ok });
        }
        else{//показать первого студента
            Student current = db.get_current_student(1);
            //создать колонки
            show_student(current);
        }
    }
    else//вывести сообщение об ошибке
        QMessageBox ask(QMessageBox::Question, "Ошибка!", "404 Файл не найден!", { QMessageBox::Ok });
}
