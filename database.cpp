#include "database.h"
#include "student.h"
#include <QMapIterator>
#include <QDataStream>

DataBase::DataBase(){}
DataBase::~DataBase(){}

int DataBase::get_current_row(Student current){
    int index = 0;
    if(position.empty())
        return index;
    QVectorIterator<int> iter(position);
    bool next = true;
    while(iter.hasNext()) {
        auto pos = main_base.find(iter.next());
        next = Student::compare_students(pos.value(), current);
        if(Student::compare_students(pos.value(), current))
            index++;
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

bool DataBase::save_to_file(QString file_name){
    QFile file(file_name);
    bool right = false;
    if(!file_name.isEmpty() && file.open(QIODevice::WriteOnly)){
        QDataStream out(&file);
        //QMapIterator<int, Student> iter(main_base);
        out << main_base;
        right = true;
    }
    modified = false;
    return right;
}

bool DataBase::load_from_file(QString file_name){
    QFile file(file_name);
    modified = true;
    bool right = false;
    if(!file_name.isEmpty() && file.open(QIODevice::WriteOnly)){
        QDataStream in(&file);
        main_base.clear();
        position.clear();
        int id; Student student;
        while(!file.atEnd()){
            in >> id >> student;
            main_base.insert(id, student);
            position.push_back(id);
        }
        right = true;
    }
    return right;
}

void DataBase::clear(){
    main_base.clear();
    position.clear();
    modified = true;
}

bool DataBase::be_modified(){ return modified;  }

QDataStream& operator<<(QDataStream& out, const DataBase& db){
    QMapIterator<int, Student> iter(db.main_base);
    while(iter.hasNext()){
        iter.next();
        out << iter.key() << iter.value();
    }
    return out;
}
QDataStream& operator>>(QDataStream& in, DataBase& db){
//    QMapIterator<int, Student> iter(db.main_base);
//    int id = 0;
//    Student current;
//    while(iter.hasNext()){
//        iter.next();
//        in >> current;
//    }
}
