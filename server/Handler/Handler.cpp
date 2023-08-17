#include "Handler.h"

#include <string>
#include <vector>
#include <memory>

#include "../Database/Database.h"
#include "../Network/Network.h"


namespace{
  //Коды запросов серверу
  enum Command{
    NOTHING,
    GET_TABLE
  };
}


/**
Сформировать таблицу в виде строки и отправить клиенту
\param[in] request Запрос клиента с параметрами таблицы
*/
static void sendTable(const std::string& request);


void handler::handle(const std::string& request)
{
  //Message - Код_Команды|АРГУМЕНТ_1:...
  //Определить код команды - от начала строки до первого '|'
  const std::string codeCommand = request.substr(0, request.find("|"));
  int command = std::stoi(codeCommand);
  switch (command){
    case GET_TABLE: {
      sendTable(request);
      break;
    default:
      break;
    }
  }
}



//-----------------------------------------------------------------------------
/**
Распарсить строку на слова по разделителю
\param[out] result Строки в которые поместить результат парсинга
\param[in] input Входная строка
\param[in] delimiter Разделитель
*/
static void parse (std::shared_ptr<std::vector<std::string> > result,
                  const std::string& input,
                  const std::string& delimiter);

/**
Преобразовать таблицу в строку символов
\param[in] table Таблица
\return Строку символов
*/
static std::string tableToString(const std::list<Line*>& table);


static void sendTable(const std::string& request)
{
  //request - Код_Команды|START_LINE|N_LINES|SORT_COLUMN|
  //Извлечь входные параметры запроса
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, request, "|");
  auto startLine = stoi(result->at(1));
  auto nLines = stoi(result->at(2));
  auto sortColumn = stoi(result->at(3));
  
  //Получить таблицу из БД
  auto table = database::getTable(startLine, nLines, sortColumn);

  //Сформировать строку для отправки клиенту
  auto tableString = tableToString(table);

  //Отправить клиенту
  network::send(tableString);
}



static std::string tableToString(const std::list<Line*>& table)
{
  std::string tableString = "";
  for(const auto& line : table){
    tableString += '\t' + std::to_string(line->firstColumn_) +
    '\t' + line->secondColumn_ +
    '\t' + std::to_string(line->thirdColumn_) + '\n';
  }
  return tableString;
}



static void parse (std::shared_ptr<std::vector<std::string> > result,
                  const std::string& input,
                  const std::string& delimiter)
{
  result->clear();
  std::string string = input;
  while (!string.empty()){
    std::string value = string.substr(0, string.find(delimiter));
    string = string.substr(string.find(delimiter)+1);
    result->push_back(value);
  }
}