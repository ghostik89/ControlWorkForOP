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

    friend QDataStream& operator<<(QDataStream& out, const DataBase& db);
    friend QDataStream& operator>>(QDataStream& in, DataBase& db);

private:
    QMap<int, Student> main_base;
    QVector<int> position;
    bool modified;
    //int last_id;
};

#endif // DATABASE_H
