#ifndef STUDENT_H
#define STUDENT_H
#include <QString>

class Student
{
public:
    Student();
    void set_FIO(QString FIO);
    void set_birthday(QString birthday);
    void set_gender(QString gender);
    void set_medal(bool medal);
    void set_middle_mark(QString middle_mark);
    void set_language(QString language);
    void set_first_exam_name(QString first_exam_name);
    void set_first_exam_score(QString first_exam_score);
    void set_second_exam_name(QString second_exam_name);
    void set_second_exam_score(QString first_second_score);
    void set_third_exam_name(QString third_exam_name);
    void set_third_exam_score(QString first_third_score);
    void set_can_pay(bool can_pay);
    Student& operator=(const Student& right);
    bool operator==(const Student& right);
    ~Student();

private:
    QString FIO;
    QString birthday;
    QString gender;
    bool medal;
    QString middle_mark;
    QString language;
    QString first_exam_name;
    QString first_exam_score;
    QString second_exam_name;
    QString second_exam_score;
    QString third_exam_name;
    QString third_exam_score;
    bool can_pay;
};

#endif // STUDENT_H
