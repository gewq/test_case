#include "Network.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Exceptions/SocketConnection_Exception.h"
#include "Exceptions/SocketCreation_Exception.h"


namespace{
  //Адрес сервера
  const std::string ADDRESS = "127.0.0.1";
  //Порт сервера
  const int PORT = 7777;
  //Максимальная длина пересылаемого сообщения
  const uint32_t MAX_LENGTH_MESSAGE = 1'000'000;

  //Дескриптор сокета клиента
  int socketDescriptor;
  //Параметры сервера
  struct sockaddr_in serverSettings;
  //Буфер приёма входящих сообщений
  char inputBuffer[MAX_LENGTH_MESSAGE];
}

/**
Создать сокет
*/
static void createSocket();

/**
Задать параметры сервера
*/
static void setSettings();

/**
Установить соединение с сервером
*/
static void setConnection();


void network::connect()
{
  createSocket();
  setSettings();
  setConnection();
}



void network::send(const std::string& message)
{
  write(socketDescriptor, message.c_str(), message.size());
}



void network::receive(std::string* message)
{
  message->clear();
  //Очистить приёмный буфер
  bzero(inputBuffer, MAX_LENGTH_MESSAGE*sizeof(char));
  //Принять входящее сообщение в приёмный буфер
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  *message = inputBuffer;
}



void network::disconnect()
{
  close(socketDescriptor);
}



//-----------------------------------------------------------------------------
/**
Создать сокет
*/
static void createSocket()
{
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(socketDescriptor == -1){
    throw SocketCreation_Exception();
  }
}



/**
Задать параметры сервера
*/
static void setSettings()
{
  serverSettings.sin_addr.s_addr = inet_addr(ADDRESS.c_str());
  serverSettings.sin_port = htons(PORT);
  serverSettings.sin_family = AF_INET;
}



/**
Установить соединение с сервером
*/
static void setConnection()
{
  int connection = connect(socketDescriptor, (struct sockaddr*)&serverSettings, sizeof(serverSettings));
  if(connection == -1){
    throw SocketConnection_Exception();
  }
}