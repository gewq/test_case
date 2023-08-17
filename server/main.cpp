#include <iostream>
#include <memory>
#include <vector>
#include <list>

#include "Network/Network.h"
#include "Database/Database.h"
#include "Handler/Handler.h"


int main()
{
  try{
    //Настроить сокет
    network::initialize();

    while(true){
      //Начать приём запросов
      network::startListen();
      std::string request = "";
      while(true){
        request.clear();
        //Получить запрос
        network::receive(&request);
        //Обработать запрос
        handler::handle(request);      
      }
    }
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