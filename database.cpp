#include "database.h"
#include "student.h"
#include <QMapIterator>

DataBase::DataBase(){}
DataBase::~DataBase(){}

int DataBase::get_current_row(Student current){
    int index = 0;
    if(position.empty())
        return index;
    //todo: сделать лучше
    for (auto iter = position.begin(); iter != position.end(); iter++) {
        auto pos = main_base.find(*iter);
        if(Student::compare_students(pos.value(), current))
            index++;
        else
            break;
    }
    return index;
}
Student DataBase::get_current_student(int id){  return main_base.find(id).value();   }

int DataBase::count(){ return position.size(); }
void DataBase::set_student(Student current, int id){
    main_base.insert(id, current);
    position.insert(position.begin() + id, id);
    modified = true;
}
void DataBase::delete_student(int id){
    main_base.erase(main_base.find(id));
    position.erase(position.begin() + id);
    modified = true;
}
void DataBase::update_db(Student current, int id){
    auto iter = main_base.find(id);
    iter.value() = current;
    modified = true;
}

bool DataBase::save_to_file(QString file_name){}
bool DataBase::load_from_file(QString file_name){}
void DataBase::clear(){
    main_base.clear();
    position.clear();
    modified = true;
}
bool DataBase::be_modified(){ return modified;  }
void DataBase::sort(){}

QDataStream& DataBase::operator<<(QDataStream& out){
//    for (auto iter = main_base.begin(); iter != main_base.end(); iter++)
//        out << iter.key() <<  iter.value();
}
QDataStream& DataBase::operator>>(QDataStream& in){}
