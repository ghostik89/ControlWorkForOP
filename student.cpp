#include "student.h"

Student::Student(){
    FIO = "Человек Человек";
    birthday = "2000.01.01";
    gender = true;
    medal = true;
    middle_mark = "4.7";
    language = "Японский";
    first_exam = std::pair<QString, QString> ("Математика I", "60");
    second_exam = std::pair<QString, QString> ("Русский", "60");
    third_exam = std::pair<QString, QString> ("Физика I", "60");
    can_pay = false;
}

Student::~Student(){}


//setters
void Student::set_first_exam(QString nfirst_exam_name, int nfirst_exam_score) {
    first_exam.first = nfirst_exam_name;
    first_exam.second = QString::number(nfirst_exam_score);
}
void Student::set_second_exam(QString nsecond_exam_name, int nsecond_exam_score){
    second_exam.first = nsecond_exam_name;
    second_exam.second = QString::number(nsecond_exam_score);
}
void Student::set_third_exam(QString nthird_exam_name, int nthird_exam_score){
    third_exam.first = nthird_exam_name;
    third_exam.second = QString::number(nthird_exam_score);
    middle_score = (first_exam.second.toInt() + second_exam.second.toInt() + third_exam.second.toInt()) / 3;
}

//getters
void Student::get_first_exam(std::pair<QString, QString> &first){
    first.first = first_exam.first;
    first.second = first_exam.second;
}
void Student::get_second_exam(std::pair<QString, QString> &second){
    second.first = second_exam.first;
    second.second = second_exam.second;
}
void Student::get_third_exam(std::pair<QString, QString> &third){
    third.first = third_exam.first;
    third.second = third_exam.second;
}

//compare
bool Student::compare_students(Student first, Student second){
    return QString::compare(first.FIO, second.FIO) > 0 && first.medal && first.middle_score > second.middle_score;
}
