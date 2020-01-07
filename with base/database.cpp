#include "database.h"
#include "student.h"
#include <QMapIterator>
#include <QDataStream>
#include <QDebug>

DataBase::DataBase(){ id = 0; }
DataBase::~DataBase(){}

int DataBase::get_current_row(Student current){
    int index = 0;//индекс новой позиции

    if(position.empty())//если новых записей не было
        return index;//то вернем нуль

    auto iter = position.begin();
    auto pos = main_base.find(*iter);
    while(iter != position.end() && pos.value() > current) {//до тех пор пока не найдется запись "больше"
        pos = main_base.find(*iter);//узнаем позицию

        //идем дальше
        iter++;
        index++;
    }
    return index;
}

Student DataBase::get_current_student(int pos){
    int elem = *(position.begin() + pos);//узнать идентификатор записи, которой мы ищем
    return main_base.find(elem).value();//найти в map
}

int DataBase::count(){ return position.length(); }

void DataBase::set_student(Student current, int pos){
    main_base.insert(id, current);
    position.insert(position.begin() + pos, id);

    modified = true;//ставим то, что изменения в бд произведены(для перегрузки закрытия)
    id++;//сгенерировать новый идентификатор
}

void DataBase::delete_student(int pos){
    auto iter = position.begin() + pos;
    main_base.erase(main_base.find(*iter));
    position.erase(iter);
    modified = true;
}

void DataBase::update_db(Student current, int id){//нигде не юзаю, рудимент
    auto iter = main_base.find(id);
    iter.value() = current;
    modified = true;
}

bool DataBase::save_to_file(QString file_name){
    QFile file(file_name);//создать файл
    bool right = false;//изначально считаем, что файл не сохранен успешно

    if(!file_name.isEmpty() && file.open(QIODevice::WriteOnly)){//если в файл можно писать и он существует
        QDataStream out(&file);//открыть поток в файл
        out << main_base << position;//записать в него саму бд и позиции в ней

        right = true;//операция прошла успешно
        file.close();//закрыть файл
    }
    modified = false;//мы все сохранили, изменить идентификатор изменений
    return right;//вернуть успешность сохранения
}

bool DataBase::load_from_file(QString file_name){
    QFile file(file_name);//создать файл
    modified = true;//текущая бд изменена
    bool right = false;//изначально считаем, что сохранение не успешно

    if(!file_name.isEmpty() && file.open(QIODevice::ReadOnly)){//если файл открыт для чтения и у него есть имя
        QDataStream in(&file);//создать поток в файл
        main_base.clear();//очистить текущую бд
        position.clear();//очистить позиции в бд

        in >> main_base >> position;//считать базу и позиции(важен порядок считывания)
        file.close();//закрыли файл
        right = true;//операция считывания проведена успешна
    }
    return right;//вернуть успешность операции
}

void DataBase::clear(){//очистить бд
    main_base.clear();
    position.clear();
    id = 0;//сбросить идентификатор
    modified = true;//были произведены изменения в бд
}

bool DataBase::be_modified(){ return modified;  }

//рудименты
QDataStream& operator<<(QDataStream& out, const DataBase& db){
//    QMapIterator<int, Student> iter(db.main_base);
//    while(iter.hasNext()){
//        iter.next();
//        out << iter.key() << iter.value();
//    }
//    return out;
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
