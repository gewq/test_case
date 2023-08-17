#include "Database.h"

namespace{
  //Таблица данных
  //- ключ - уникальный идентификатор строки
  //- значение - сама строка.
  std::map<size_t, Line> table = {
    {21, {423, "Dog", 34623.234}},
    {23, {23141, "Cat", -6543.23}},
    {34, {52315, "Bird", 214.1}},
    {52, {125312, "Lion", 0.4}},
    {64, {1235, "Tiger", 423.2}},
    {74, {4345, "Cow", 42.315}},
    {78, {1234, "Goat", 427.78}},
    {89, {7897, "Pig", 978.24}},
    {99, {78, "Frog", 777.57}},
    {210, {78976, "Snake", 1.5}}
  };
}



void database::addLine(size_t ID, const Line& line)
{
  table.emplace(std::pair<size_t, Line>(ID, line));
}



void database::removeLine(size_t ID)
{
  table.erase(ID);
}



/**
Отсортировать таблицу по заданному столбцу
\param[out] table Отсортированная таблица
\param[in] sortColumn Номер столбца по которому сортировать
*/
static void sortTable(std::list<Line*>* table, size_t sortColumn);

/**
Сделать выборку из таблицы
\param[in] startLine Начальная строка (номер записи в таблице)
\param[in] nLines Количество строк
\return Список указателей на строки таблицы
*/
static std::list<Line*> fetchTable(size_t startLine, size_t nLines);


std::list<Line*> database::getTable(size_t startLine, size_t nLines, size_t sortColumn)
{
  //Получить выборку из таблицы
  auto table = fetchTable(startLine, nLines);
  //Отсортировать выборку по столбцу
  sortTable(&table, sortColumn);
  return table;
}



//-----------------------------------------------------------------------------
static std::list<Line*> fetchTable(size_t startLine, size_t nLines)
{
  std::list<Line*> lines;
  auto iter = table.begin();
  //Пропустить первые startLine-1 строк  
  size_t pos = 1;
  while(pos != startLine){
    ++pos;
    ++iter;
  }
  //Записать следующие nLines строк
  for(size_t i=0; i<nLines; ++i){
    if (iter == table.end()){
      break;
    }
    lines.push_back(&table.at(iter->first));
    ++iter;
  }
  return lines;
}



static void sortTable(std::list<Line*>* table, size_t sortColumn)
{
  if (sortColumn == 1){
    table->sort([](Line* line_1, Line* line_2){
      return line_1->firstColumn_ > line_2->firstColumn_;
    });
  }

  if (sortColumn == 2){
    table->sort([](Line* line_1, Line* line_2){
      if(line_1->secondColumn_.compare(line_2->secondColumn_) > 0){
        return false;
      }
      return true;
    });
  }

  if (sortColumn == 3){
    table->sort([](Line* line_1, Line* line_2){
      return line_1->thirdColumn_ > line_2->thirdColumn_;
    });
  }
}