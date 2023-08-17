#pragma once

#include <iostream>


namespace network{
  /**
  Настроить сетевое соединение
  */
  void initialize();

  /**
  Начать прослушивать порт и принимать входящие запросы
  */
  void startListen();

  /**
  Получить сообщение
  \param[out] message Полученное сообщение 
  */
  void receive(std::string* message);

  /**
  Отправить сообщение
  \param[in] message Сообщение
  */
  void send(const std::string& message);

  /**
  Закрыть сетевое соединение
  */  
  void disconnect();
}