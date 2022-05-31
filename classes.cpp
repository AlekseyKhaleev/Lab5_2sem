
#include "classes.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstring>

using namespace Person_const;

PrsPtr IPerson::CreateInstance(int id){
    switch(id/1000){
        case 21: return std::make_shared<Bachelor>();
        case 22: return std::make_shared<Master>();
        case 23: return std::make_shared<Graduate>();
        default: throw std::exception();
    }
}



/* Person */
Person::Person() = default;
Person::~Person() = default;

void Person::set_surname() {std::cin >> _surname;}
void Person::set_name() {std::cin>>_name;}
void Person::set_id(int id) {_id = std::to_string(id);}
void Person::set_id(char *id) {_id = id;}


/* Student */
Student::Student(){_category="студент";}
Student::~Student() = default;

void Student::set_exp() {
    std::cin>>_exp;
    _exp += " курс";
}

string Student::get_exp() {return _exp;}
string Student::get_category() {return _category;}

//sub_class
Bachelor::Bachelor():Student(){_info="бакалавриат";}
Bachelor::~Bachelor() = default;

string Bachelor::get_info() {return _info;}

//sub_class
Master::Master():Student() {_info = "магистратура";}
Master::~Master() = default;
string Master::get_info() {return _info;}

//sub_class
Graduate::Graduate():Student() {_info = "аспирантура";}
Graduate::~Graduate() = default;
string Graduate::get_info() {return _info;}

// friend classes
void InitInstance(PrsPtr &ptr, int row_to_print){
    static std::vector<int> IDs;
    int id, current_col{START_COL};
    move_cursor(START_ROW + row_to_print * STEP_ROW, START_COL);
    std::cin >> id;
    for(auto &elem:IDs){
        if (elem == id) throw std::exception();
    }
    ptr = IPerson::CreateInstance(id);
    IDs.push_back(id);
    ptr->set_id(id);
    move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL); // перемещение курсора
    ptr->set_surname();
    move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL); // перемещение курсора
    ptr->set_name();
    move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL); // перемещение курсора
    std::cout<<ptr->_category;
    move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL); // перемещение курсора
    ptr->set_exp();
    move_cursor(START_ROW + row_to_print * STEP_ROW, current_col); // перемещение курсора
    std::cout<<ptr->_exp;
    move_cursor(START_ROW + row_to_print * STEP_ROW, current_col += STEP_COL); // перемещение курсора
    std::cout<<ptr->_info;
}
void PrintInstance(const PrsPtr& ptr, int start_row) {
    int current_col = START_COL;
    move_cursor(START_ROW + start_row * STEP_ROW, START_COL);
    for(auto &_attribute:ptr->_attributes){ // обход аттрибутов объекта через указатели
        std::cout << *_attribute; // вывод
        move_cursor(START_ROW + start_row * STEP_ROW, current_col += STEP_COL); // перемещение курсора
    }
}

void WriteInstance(PrsPtr &ptr, std::fstream &fd) {
    /*****************************************************************************************************************
    * Цель: Запись атрибутов объекта в файл.
    * Исходные данные:
    *   fd - поток с файловым дескриптором fd
    * Результат: данные атрибутов объекта записаны в файл.
    * Вызываемые модули: <fstream>, <iostream>
    * Описание алгоритма:
    * Все объекты имеют пользовательский тип(класс) String. Для каждого атрибута:
    * 1) С помощью метода get_size() в переменную записывается размер массива символов, содержащихся в значении атрибута
    * 2) В файл записывается полученный размер
    * 3) В файл записывается сам массив, полученный с помощью метода get() и являющийся значением атрибута
    * Дата: 23 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/
    for(auto &_attribute:ptr->_attributes_wr){ // обход атрибутов экземпляра класса с помощью указателей
        std::size_t attr_size = strlen(_attribute->c_str()); //узнаем размер
        fd.write((char *) &attr_size, sizeof(std::size_t)); // записываем размер в файл
        fd.write((char *) &*_attribute->c_str(), long(attr_size));  // записываем массив char* полученного размера,
        // соответствующий атрибуту в файл
    }
}

void ReadInstance(PrsPtr &ptr, std::fstream &fd) {
    /*****************************************************************************************************************
    * Цель: Чтение из файла атрибутов объекта.
    * Исходные данные:
    *   fd - поток с файловым дескриптором fd
    * Результат: данные атрибутов объекта записаны в файл.
    * Вызываемые модули: <fstream>, <iostream>
    * Описание алгоритма:
    * Все объекты имеют пользовательский тип(класс) String. Для каждого атрибута:
    * 1) Объявляется переменная пользовательского типа для хранения размера массива char*, соответствующего атрибуту
    * 2) Из файла считывается размер массива char*, соответствующего атрибуту
    * 3) Объявляется переменная типа char* для чтения массива считанного размера из файла. Память выделяется в стеке
    * 4) С помощью объявленной переменной производится чтение из потока массива char*, соответствующего атрибуту
    * 5) С помощью перегруженного оператора присваивания для класса(типа) String производится инициализация атрибута
    * считанным значением (с выделением динамеческой памяти "под капотом", будет освобождена при уничтожении экземпляра
    * деструктором)
    * Дата: 23 / 05 / 2022 Версия 1.01
    * Автор: Студент НГТУ ИРИТ, Халеев А. А. гр. 21-ИВТз
    * Исправления: нет
    *****************************************************************************************************************/
    std::size_t id_size{0}; // объявляем переменную для считывания размера массива char* (атрибута)
    fd.read((char *) &id_size, sizeof(std::size_t)); // считываем размер
    char ch_id[id_size]; // выделяем память в стеке под будущий массив
    fd.read((char *) &ch_id, long(id_size)); // считываем данные (элементы) массива char* атрибута
    int id = std::stoi(ch_id);
    ptr = IPerson::CreateInstance(id);
    ptr->set_id(id);
    for(int i=1;i<NUMB_OF_ATTR_WR;i++){ // обход атрибутов экземпляра класса с помощью указателей
        std::size_t attr_size{0}; // объявляем переменную для считывания размера массива char* (атрибута)
        fd.read((char *) &attr_size, sizeof(std::size_t)); // считываем размер
        char content[attr_size]; // выделяем память в стеке под будущий массив
        fd.read((char *) &content, long(attr_size)); // считываем данные (элементы) массива char* атрибута
        for(auto &ch:content) {
            *ptr->_attributes_wr[i] += ch; // инициализируем атрибут
        }
    }
}
