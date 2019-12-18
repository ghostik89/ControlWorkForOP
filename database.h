#ifndef DATABASE_H
#define DATABASE_H
#include <QMap>
#include <QMapIterator>
#include <QFile>
#include <QVector>
#include "student.h"

class DataBase
{
public:
    DataBase();
    ~DataBase();

    int get_current_row(Student current);
    Student get_current_student(int id);

    int count();
    void set_student(Student current, int id);
    void delete_student(int id);
    void update_db(Student cuurent, int id);
    bool save_to_file(QString file_name);
    bool load_from_file(QString file_name);
    void clear();
    bool be_modified();
    void sort();

    QDataStream& operator<<(QDataStream& out);
    QDataStream& operator>>(QDataStream& in);

private:
    QMap<int, Student> main_base;
    QVector<int> position;
    bool modified;
};

#endif // DATABASE_H
