#include "Network.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Exceptions/MaxClients_Exception.h"
#include "Exceptions/SocketBinding_Exception.h"
#include "Exceptions/SocketConnection_Exception.h"
#include "Exceptions/SocketCreation_Exception.h"


namespace{
  //Порт сервера
  const int PORT = 7777;
  //Максимальное количество очереди клиентов
  const int MAX_CLIENTS = 5;
  //Максимальная длина пересылаемого сообщения
  const uint32_t MAX_LENGTH_MESSAGE = 1'000'000;
  //Дескриптор сокета сервера - прослушивающего сеть
  int socketDescriptor;
  //Дескриптор сокета для взаимодействия с клиентом
  int clientDescriptor;

  socklen_t length;
  struct sockaddr_in serverSettings;
  struct sockaddr_in client;

  //Буфер приёма входящих сообщений 
  char inputBuffer[MAX_LENGTH_MESSAGE];
  std::string message;
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
Привязать сокет к сетевым параметрам
*/
static void bindSocket();


void network::initialize()
{
  createSocket();
  setSettings();
  bindSocket();
}



void network::startListen()
{
  //Сервер на приём данных
  int connectionStatus = listen(socketDescriptor, MAX_CLIENTS);
  if (connectionStatus == -1){
    throw MaxClientExceeds_Exception();
  }
  std::cout << "Server is ready to new connections..." << std::endl;
  length = sizeof(client);
  clientDescriptor = accept(socketDescriptor,
                      (struct sockaddr*)&client,
                      &length);
  if (clientDescriptor == -1){
    throw SocketConnection_Exception();
  }
}



void network::receive(std::string* message)
{
  message->clear();
  //Очистить приёмный буфер
  bzero(inputBuffer, MAX_LENGTH_MESSAGE*sizeof(char));
  read(clientDescriptor, inputBuffer, sizeof(*message));
  *message = inputBuffer;
}



void network::send(const std::string& message)
{
  write(clientDescriptor, message.c_str(), message.size());
}



void network::disconnect()
{
  close(socketDescriptor);
}



static void createSocket()
{
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor == -1){
    throw SocketCreation_Exception();
  }
}



static void setSettings()
{
  serverSettings.sin_addr.s_addr = htonl(INADDR_ANY);  //Приём на все сетевые интерфейсы
  serverSettings.sin_port = htons(PORT); //Порт
  serverSettings.sin_family = AF_INET;   //IPv4
}



static void bindSocket()
{
  int bind_status = bind(socketDescriptor,
                        (struct sockaddr*) &serverSettings,
                        sizeof(serverSettings));
  if (bind_status == -1){
    throw SocketBinding_Exception();
  }
}