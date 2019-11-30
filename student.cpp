#include "student.h"

Student::Student(){}

Student::~Student(){}


//setters
void Student::set_FIO(QString new_FIO){ FIO = new_FIO; }
void Student::set_birthday(QString new_birthday){ birthday = new_birthday; }
void Student::set_gender(QString new_gender){   gender = new_gender;    }
void Student::set_medal(bool new_medal){    medal = new_medal;  }
void Student::set_middle_mark(QString new_middle_mark){ middle_mark = new_middle_mark;  }
void Student::set_language(QString new_language){   language = new_language;    }
void Student::set_first_exam_name(QString new_first_exam_name){ first_exam_name = new_first_exam_name;  }
void Student::set_second_exam_name(QString new_second_exam_name){   second_exam_name = new_second_exam_name;    }
void Student::set_third_exam_name(QString new_third_exam_name){ third_exam_name = new_third_exam_name;  }
void Student::set_can_pay(bool new_can_pay){    can_pay = new_can_pay;  }


//операторы
bool Student::operator==(const Student& right){
    return FIO == right.FIO && birthday == right.birthday && gender == right.gender && medal == right.medal && middle_mark == right.middle_mark &&
            language == right.language && first_exam_name == right.first_exam_name && first_exam_name == right.first_exam_name && first_exam_name == right.first_exam_name &&
            first_exam_score == right.first_exam_score && second_exam_name == right.second_exam_name && second_exam_score == right.second_exam_score &&
            third_exam_name == right.third_exam_name && third_exam_score == right.third_exam_score && can_pay == right.can_pay;
}

Student& Student::operator=(const Student& right){
    if(this == &right)
        return *this;

    FIO = right.FIO;
    birthday = right.birthday;
    gender = right.gender;
    medal = right.medal;
    middle_mark = right.middle_mark;
    language = right.language;
    first_exam_name = right.first_exam_name;
    first_exam_score = right.first_exam_score;
    second_exam_name = right.second_exam_name;
    second_exam_score = right.second_exam_score;
    third_exam_name = right.third_exam_name;
    third_exam_score = right.third_exam_score;
    can_pay = right.can_pay;

    return *this;
}



