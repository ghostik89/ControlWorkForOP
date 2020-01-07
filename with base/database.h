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

    ///
    /// \brief get_current_row - функция для получения позиции нового элемента в списке
    /// \param current - новый элемент
    /// \return позиция в списке
    ///
    int get_current_row(Student current);

    ///
    /// \brief get_current_student - получить запись по положению в списке
    /// \param id - положение в списке
    /// \return - запись
    ///
    Student get_current_student(int id);

    ///
    /// \brief count - получение общего количества записей
    /// \return - количество записей
    ///
    int count();

    ///
    /// \brief set_student - добавить новую запись в базу данных
    /// \param current - новая запись
    /// \param id - ее ключ
    ///
    void set_student(Student current, int id);

    ///
    /// \brief delete_student - удалить запись из базы данных
    /// \param id - id записи, котороую нужно удалить
    ///
    void delete_student(int id);

    ///
    /// \brief update_db - обновить значение в базе данных
    /// \param cuurent - значение, которое нужно обновить
    /// \param id - ее id
    ///
    void update_db(Student cuurent, int id);

    ///
    /// \brief save_to_file - сохранить в файл базу данных
    /// \param file_name - имя файла
    /// \return - успешность завершения сохранения
    ///
    bool save_to_file(QString file_name);

    ///
    /// \brief load_from_file - считать с файла базу данных
    /// \param file_name - имя файла
    /// \return - успешность завершения операции
    ///
    bool load_from_file(QString file_name);

    ///
    /// \brief clear - очистить базу данных
    ///
    void clear();

    ///
    /// \brief be_modified - узнать произошли ли изменения в базе данных
    /// \return - были ли изменения в базе данных
    ///
    bool be_modified();

    friend QDataStream& operator<<(QDataStream& out, const DataBase& db);
    friend QDataStream& operator>>(QDataStream& in, DataBase& db);

private:
    QMap<int, Student> main_base;//база данных
    QVector<int> position;//хранение позиции
    bool modified;//идентефикатор изменений в БД
    int id;//уникальный идентификатор для каждой записи
    //int last_id;
};

#endif // DATABASE_H
