/**********************************************************************************************************************
* Данный модуль содержит определения функций, предназначенных для работы с таблицей (создание, инициализация, вывод)
***********************************************************************************************************************/

#pragma once

/* Подключение модулей*/
#include <array>
#include <fstream>
#include "lib_definitions.h"
#include "lib_classes.h"


/* Функция вызова исключения связанного с выделением памяти для передачи в set_new_handler() */
void NewError();

/* Считывание кода нажатой клавиши в терминале без промежуточной буферизации */
int UserKey();

/* Печать указанного количества строк таблицы, начиная с указанной строки */
void PrintTable(PrsPtr Persons[], int rows_request, int row_number);

/* Запись в бинарный файл данных таблицы, введенных пользователем */
int CreateTable(char *argv[], std::fstream &table_out, int rows_request);

/* Просмотр таблицы, с поддержкой управляющих клавиш */
void ViewTable(char *argv[], std::fstream &table_in, int rows_request, int row_number=0);

/* Вывод страницы с таблицей */
void GenerateTablePage(PrsPtr Persons[], char* argv[], int rows_to_print, int real_rows, int row_number);
