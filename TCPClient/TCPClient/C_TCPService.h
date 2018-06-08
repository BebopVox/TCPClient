#pragma once

#ifndef DEFAULT_PORT
#define DEFAULT_PORT "6881"
#endif // DEFAULT_PORT

class C_TCPService
{
public:

  static int Send(SOCKET socket, char* pszMsg, int iMsgSize);
  static int Receive(SOCKET socket, char* pszBuff, int iBufSize);

private:

};
