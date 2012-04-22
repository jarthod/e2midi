#ifndef OUTPUT_TCP_HPP
#define OUTPUT_TCP_HPP

#include <TcpServer.h>
#include "output.hpp"

class TCPOutput : public Output {
public:
  TCPOutput();
  void    trigger(float p);

private:
  stk::TcpServer server;
  int             client;
};

#endif