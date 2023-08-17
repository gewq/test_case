/**
\file Handler.h
\brief Логика обработки запросов серверу
*/


#pragma once

#include <string>

namespace handler{
  /**
  Обработать запрос и отправить ответ клиенту
  \param[in] request Запрос клиента
  */
  void handle(const std::string& request);
}