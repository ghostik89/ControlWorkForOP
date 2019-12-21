#include "student.h"
#include <cstdlib>
#include <map>
#include <QString>
#include <string>

using namespace std;

Student::Student(){
    FIO = "Человек Человек";
    birthday = "2000.01.01";
    gender = true;
    medal = true;
    middle_mark = "3.0";
    language = "Японский";
    first_exam = std::pair<QString, QString> ("Математика I", "0");
    second_exam = std::pair<QString, QString> ("Русский", "0");
    third_exam = std::pair<QString, QString> ("Физика I", "0");
    can_pay = false;
}
Student::~Student(){}
Student::Student(QString nFIO, QDate nbirthday, QString ngender){
    FIO = nFIO; birthday = nbirthday.toString(); gender = ngender;
    medal = false;
    middle_mark = 3.0 + rand()%(5 - 3 + 1);
    language = medal ? "Японский": "Английский";
    first_exam = std::pair<QString, QString> ("Математика I", QString::number(0 + rand()%(100 - 0 + 1)));
    second_exam = std::pair<QString, QString> ("Русский язык", QString::number(0 + rand()%(100 - 0 + 1)));
    third_exam = std::pair<QString, QString> ("Математика I", QString::number(0 + rand()%(100 - 0 + 1)));

    middle_score = (first_exam.second.toInt() + second_exam.second.toInt() + third_exam.second.toInt()) / 3;
    if(middle_score < 50.5){
        can_pay = true;
        bill = 12000 + rand() % 3200;
    }
}

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
bool Student::operator==(const Student& right){
    return FIO == right.FIO && right.bill == bill && right.medal && medal
            && right.gender == gender && right.can_pay && can_pay && right.birthday == birthday &&
            right.first_exam == first_exam && right.second_exam == second_exam && right.third_exam == third_exam
            && right.middle_mark == middle_mark && right.middle_score == middle_score;
}
Student& Student::operator=(const Student& right){
    if(this == &right)
        return *this;
    FIO = right.FIO;
    bill = right.bill;
    medal = right.medal;
    gender = right.gender;
    can_pay = right.can_pay;
    birthday = right.birthday;
    first_exam = right.first_exam;
    second_exam = right.second_exam;
    third_exam = right.third_exam;
    middle_mark = right.middle_mark;
    middle_score = right.middle_score;

    return *this;
}

QDataStream& operator<<(QDataStream &out, const Student& current){
    out << current.FIO << current.bill
        << current.gender << current.birthday << current.language
        << current.first_exam.first << current.first_exam.second
        << current.second_exam.first << current.second_exam.second
        << current.third_exam.first << current.third_exam.second
        << current.middle_mark;
}
QDataStream& operator>>(QDataStream& in, Student& current){
    in  >> current.FIO >> current.bill
        >> current.gender >> current.birthday >> current.language
        >> current.first_exam.first >> current.first_exam.second
        >> current.second_exam.first >> current.second_exam.second
        >> current.third_exam.first >> current.third_exam.second
        >> current.middle_mark;

    current.middle_mark = (current.first_exam.second.toInt() + current.second_exam.second.toInt() + current.third_exam.second.toInt()) / 3;
    current.can_pay = current.bill == "0";
}
