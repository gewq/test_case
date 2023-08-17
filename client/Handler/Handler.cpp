#include "Handler.h"

#include "Network/Network.h"


namespace{
  //Коды запросов серверу
  enum Command{
    NOTHING,
    //Получить выборку из таблицы
    GET_TABLE
  };
}



void handler::requestTable(size_t startLine,
                          size_t nLines,
                          size_t sortColumn,
                          std::string* table)
{
  //request - Код_Команды|START_LINE|N_LINES|COLUMN_SORT|
  //Сформировать запрос
  Command command = GET_TABLE;
  std::string message = std::to_string(command) +
                        "|" + std::to_string(startLine) +
                        "|" + std::to_string(nLines) +
                        "|" + std::to_string(sortColumn) + "|";
  //Отправить запрос
  network::send(message);
  //Ждать ответ от сервера
  network::receive(table);
}
