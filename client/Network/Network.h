#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>


namespace network{
  /**
  Подключиться к серверу
  */
  void connect();

  /**
  Отправить сообщение
  \param[in] message Сообщение
  */
  void send(const std::string& message);

  /**
  Получить сообщение
  \param[in] message Сообщение
  */
  void receive(std::string* message);

  /**
  Завершить сетевое соединение
  */
  void disconnect();
}