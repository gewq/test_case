/**
\file Handler.h
\brief Запросы серверу
*/


#pragma once

#include <string>

namespace handler{
  /**
  Запросить у сервера выборку строк из БД
  \param[in] startLine Начальная строка (номер записи в таблице)
  \param[in] nLines Количество строк
  \param[in] sortColumn Номер столбца по которому сортировать результат
  \param[in] table Таблица в виде строки
  */
  void requestTable(size_t startLine,
                    size_t nLines,
                    size_t sortColumn,
                    std::string* table);
}