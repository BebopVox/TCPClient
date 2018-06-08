#pragma once

#include <WinSock2.h>

#pragma comment (lib, "Ws2_32.lib")

class C_TCPClientNetwork
{
public:
  // ctor/dtor
  C_TCPClientNetwork();
  ~C_TCPClientNetwork();

  unsigned int receivePackets(char* pszRecvBuf);

//private:
  // for error checking function calls in Winsock library
  unsigned int m_uiResult;

  // socket for client to connect to server
  SOCKET m_Socket;
};

