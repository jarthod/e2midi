#include "output_tcp.hpp"
#include "stdio.h"
#include "string.h"
#include <iostream>

TCPOutput::TCPOutput() : server(2012)
{
  stk::TcpServer::setBlocking(server.id(), false);
  std::cout << "TCPOutput waiting for client on port: " << server.port() << std::endl;
}

void  TCPOutput::trigger(float p)
{
  char  buffer[10];
  sprintf(buffer, "%4.2f\n", p);
  int client;
  if ((client = server.accept()) > 0) {
    std::cout << "New client: " << client << std::endl;
    clients.insert(client);
  }
  std::cout << "TCPOutput trigger: " << p << std::endl;

  std::set<int>::iterator it;
  for (it = clients.begin(); it != clients.end(); it++) {
    client = *it;    
    int ret = stk::Socket::writeBuffer(client, buffer, strlen(buffer), 0);
    if (ret == -1) {
      std::cout << "Client disconnected" << std::endl;
      clients.erase(client);
    }    
  }
}