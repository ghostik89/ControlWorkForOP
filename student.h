#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <map>
#include <QDate>

class Student
{
public:
    Student();
    //setters
    void set_FIO(QString new_FIO){ FIO = new_FIO; }
    void set_birthday(QString new_birthday){ birthday = new_birthday; }
    void set_gender(QString new_gender){ gender = new_gender;   }
    void set_medal(bool new_medal){    medal = new_medal;  }
    void set_middle_mark(double new_middle_mark) { middle_mark = QString::number(new_middle_mark); }
    void set_language(QString new_language){   language = new_language;    }
    void set_first_exam(QString nfirst_exam_name, int nfirst_exam_score);
    void set_second_exam(QString nsecond_exam_name, int nsecond_exam_score);
    void set_third_exam(QString nthird_exam_name, int nthird_exam_score);
    void set_can_pay(bool new_can_pay){    can_pay = new_can_pay;  }

    //getters
    QString get_FIO() { return FIO; }
    QDate get_birthday() { return QDate::fromString(birthday); }
    bool get_gender() {  return gender == "Мужской" ? true : false; }
    bool get_medal() {  return medal; }
    double get_middle_mark() {  return middle_mark.toDouble(); }
    QString get_language() {return language; }
    void get_first_exam(std::pair<QString, QString> &first);
    void get_second_exam(std::pair<QString, QString> &second);
    void get_third_exam(std::pair<QString, QString> &third);
    bool get_can_pay() { return can_pay; }
    ~Student();

private:
    QString FIO;
    QString birthday;
    QString gender;
    bool medal;
    QString middle_mark;
    QString language;
    std::pair<QString, QString> first_exam;
    std::pair<QString, QString> second_exam;
    std::pair<QString, QString> third_exam;
    bool can_pay;
};

#endif // STUDENT_H
