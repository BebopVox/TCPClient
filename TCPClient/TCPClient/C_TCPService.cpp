#include <WinSock2.h>

#include "C_TCPService.h"

int C_TCPService::Send(SOCKET socket, char* pszMsg, int iMsgSize)
{
  return send(socket, pszMsg, iMsgSize, 0);
}

int C_TCPService::Receive(SOCKET socket, char* pszBuff, int iBufSize)
{
  return recv(socket, pszBuff, iBufSize, 0);
}
