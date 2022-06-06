/*********************************************************************************************************************
* Данный модуль содержит определения иерархии классов, предназначенных для работы с таблицей данных отдела кадров
* (приложение Lab5-2)
*********************************************************************************************************************/
#pragma once

/*Подключение модулей*/
#include <memory>
#include <string>
#include <fstream>

/* Константы и макроопределения, используемые для работы с классами */
namespace Person_const {

#define ESC                     "\x1B" // начало выражения
    /* переместить курсор в строку row и позицию col */
#define move_cursor(row, col)   std::cout << ESC "[" << (row) << ";" << (col) << "H"

    const int START_ROW = 15;  // Номер строки для начала ввода/вывода данных таблицы
    const int START_ROW_FR = 11;  // Номер строки для начала отрисовки таблицы (FR - Frame)
    const int START_COL = 7;   // Позиция курсора для начала ввода/вывода данных таблицы
    const int STEP_COL = 17;  // Шаг для перемещения позиции курсора при выводе таблицы
    const int STEP_ROW = 3;   // Шаг для перемещения по строкам курсора при выводе таблицы
    const int NUMB_OF_ATTR = 6;
    const int NUMB_OF_ATTR_WR = 4;
}

/* Определения для удобства работы с классами */
class IPerson;
using PrsPtr = std::shared_ptr<IPerson>;
using string = std::string;
using namespace Person_const;

// интерфейсный класс
class IPerson{
protected:
    virtual ~IPerson() = default; // защищенный деструктор
    IPerson& operator=(const IPerson&) = default; // запрет присваивания
    [[nodiscard]] static PrsPtr CreateInstance(int target); // функция-фабрика

    virtual void set_id(int id)=0;
    virtual void set_surname()=0;
    virtual void set_name()=0;
    virtual void set_exp()=0;
    virtual string get_exp()=0;
    virtual string get_category()=0;
    virtual string get_info()=0;
    virtual string** get_attr_wr()=0;

public:
    [[nodiscard]]static PrsPtr InitInstance(int row_to_print);
    [[nodiscard]]static PrsPtr ReadInstance(std::fstream &fd);
    virtual void WriteInstance(std::fstream &fd)=0;
    virtual void PrintInstance(int start_row)=0;
};

// класс реализации
class Person : public IPerson{
protected:
    string _id;
    string _surname;
    string _name;
    string _exp;
    string _category;
    string _info;
    string* _attributes[NUMB_OF_ATTR]{&_id,&_surname, &_name, &_category, &_exp, &_info };
    string* _attributes_wr[NUMB_OF_ATTR_WR]{&_id,&_surname, &_name, &_exp};
public:
    Person();  // открытый конструктор
    ~Person() override; // открытый деструктор

    void set_name() override;
    void set_id(int id) override;
    void set_surname() override;
    void set_exp() override;
    string get_exp() override;
    string get_info() override;
    string get_category() override;
    string** get_attr_wr() override;
    void WriteInstance(std::fstream &fd) override;
    void PrintInstance(int start_row) override;
};

// класс реализации
class Student : public Person{
public:
    Student();  // открытый конструктор
    ~Student() override; // открытый деструктор
protected:
    void set_exp() override;
};

// класс реализации
class Bachelor final : public Student{
public:
    Bachelor();  // открытый конструктор
    ~Bachelor() final; // открытый деструктор
};

// класс реализации
class Master final : public Student{
public:
    Master();  // открытый конструктор
    ~Master() final; // открытый деструктор
};

// класс реализации
class Graduate final : public Student{
public:
    Graduate();  // открытый конструктор
    ~Graduate() final; // открытый деструктор
};

// класс реализации
class Employee : public Person{
public:
    Employee();  // открытый конструктор
    ~Employee() override; // открытый деструктор
protected:
    void set_exp() override;
};

// класс реализации
class Teacher final : public Employee{
public:
    Teacher();  // открытый конструктор
    ~Teacher() final; // открытый деструктор
};

// класс реализации
class Assistant final : public Employee{
public:
    Assistant();  // открытый конструктор
    ~Assistant() final; // открытый деструктор
};

// класс реализации
class HouseKeeper final : public Employee{
public:
    HouseKeeper();  // открытый конструктор
    ~HouseKeeper() final; // открытый деструктор
};

