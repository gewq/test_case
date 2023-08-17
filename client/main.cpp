/**
\file main.cpp
\brief Отображение N строк таблицы, запрошенной у сервера

Запрошенный участок таблицы передаётся в виде std::string и выводится в консоль
*/


#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Network/Network.h"
#include "Handler/Handler.h"


int main(){
  try{
    //Подключиться к серверу
    network::connect();

    std::string request;  //Запрос серверу
    std::string table;    //Участок таблицы, полученный от сервера
    //Взаимодействие с сервером
    while(true){
      request.clear();
      table.clear();
      //Запрос параметров таблицы для сервера
      size_t startLine = 0;
      std::cout << "Input startLine: ";
      std::cin >> startLine;

      size_t nLines = 0;
      std::cout << "Input nLines: ";
      std::cin >> nLines;

      size_t sortColumn = 0;
      std::cout << "Input sortColumn: ";
      std::cin >> sortColumn;

      //Запросить таблицу у сервера
      handler::requestTable(startLine, nLines, sortColumn, &table);
      //Отобразить таблицу
      std::cout << table << std::endl;
    }
    //Завершить соединение
    network::disconnect();
  }
  catch (std::exception& error) {
    std::cerr << error.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Undefined exception" << std::endl;
  }
  return EXIT_SUCCESS;
}