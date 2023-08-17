/**
\file Database.h
\brief Содержит базу данных в виде таблицы

Предоставляет методы:
- добавить строку
- удалить строку
- получить отсортированную выборку из N строк, начиная с заданной, по
  заданному столбцу
*/


#pragma once

#include <iostream>
#include <string>
#include <map>
#include <list>


//Строка таблицы - представляет совокупность значений трёх столбцов
struct Line{
  int firstColumn_;
  std::string secondColumn_;
  double thirdColumn_;

  Line():firstColumn_(0), secondColumn_("empty"), thirdColumn_(0.0){}
  Line(int col_1, std::string col_2, double col_3):
    firstColumn_(col_1), secondColumn_(col_2), thirdColumn_(col_3){}
};



namespace database{
  /**
  Добавить строку в таблицу
  \param[in] id Уникальный идентификатор строки
  \param[in] line Строка данных
  */
  void addLine(size_t id, const Line& line);

  /**
  Удалить строку из таблицы
  \param[in] id Уникальный идентификатор строки
  */
  void removeLine(size_t id);

  /**
  Сделать выборку из таблицы
  \param[in] startLine Начальная строка (номер записи в таблице)
  \param[in] nLines Количество строк
  \param[in] sortColumn Номер столбца по которому сортировать
  \return Список указателей на строки таблицы
  */
  std::list<Line*> getTable(size_t startLine, size_t nLines, size_t sortColumn);
}