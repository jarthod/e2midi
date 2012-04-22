#include "output_tcp.hpp"
#include "stdio.h"
#include "string.h"
#include <iostream>

TCPOutput::TCPOutput() : server(2012)
{
//  stk::TcpServer::setBlocking(server.id(), false);
  std::cout << "TCPOutput waiting for client on port: " << server.port() << std::endl;
  client = server.accept();
}

void  TCPOutput::trigger(float p)
{
  char  buffer[10];
  sprintf(buffer, "%4.2f\n", p);
  std::cout << "TCPOutput trigger: " << p << std::endl;
  if (client > 0) {
    int ret = stk::Socket::writeBuffer(client, buffer, strlen(buffer), 0);
    if (ret == -1) {
      std::cout << "Client disconnected" << std::endl;
      client = -1;
    }    
  }
}