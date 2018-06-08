#include <iostream>
#include <ws2tcpip.h>

#include "C_TCPService.h"
#include "C_NetPacket.h"

#include "C_TCPClientNetwork.h"

using namespace std;

C_TCPClientNetwork::C_TCPClientNetwork()
{
  // create WSADATA object
  WSADATA wsaData;

  // socket
  m_Socket = INVALID_SOCKET;

  // holds address info for socket to connect to
  struct addrinfo* pAIResult = NULL;
  struct addrinfo* pAITemp = NULL;
  struct addrinfo addrInfoHints;

  // Initialize Winsock
  m_uiResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

  if (m_uiResult != 0)
  {
    cout << "WSAStartup failed with error: " << m_uiResult << endl;
    exit(1);
  }

  // set address info
  ZeroMemory(&addrInfoHints, sizeof(addrInfoHints));
  addrInfoHints.ai_family = AF_UNSPEC;
  addrInfoHints.ai_socktype = SOCK_STREAM;
  addrInfoHints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!

  //resolve server address and port 
  m_uiResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &addrInfoHints, &pAIResult);

  if (m_uiResult != 0)
  {
    cout << "getaddrinfo failed with error: " << m_uiResult << endl;
    WSACleanup();
    exit(1);
  }

  // Attempt to connect to an address until one succeeds
  for (pAITemp = pAIResult; pAITemp != NULL; pAITemp = pAITemp->ai_next)
  {
    // Create a SOCKET for connecting to server
    m_Socket = socket(pAITemp->ai_family, pAITemp->ai_socktype, pAITemp->ai_protocol);

    if (m_Socket == INVALID_SOCKET)
    {
      printf("socket failed with error: %ld\n", WSAGetLastError());
      WSACleanup();
      exit(1);
    }

    // Connect to server.
    m_uiResult = connect(m_Socket, pAITemp->ai_addr, (int)pAITemp->ai_addrlen);

    if (m_uiResult == SOCKET_ERROR)
    {
      closesocket(m_Socket);
      m_Socket = INVALID_SOCKET;
      printf("The server is down... did not connect");
    }
  }

  // no longer need address info for server
  freeaddrinfo(pAIResult);

  // if connection failed
  if (m_Socket == INVALID_SOCKET)
  {
    printf("Unable to connect to server!\n");
    WSACleanup();
    exit(1);
  }

  // Set the mode of the socket to be nonblocking
  unsigned long ulMode = 1;

  m_uiResult = ioctlsocket(m_Socket, FIONBIO, &ulMode);

  if (m_uiResult == SOCKET_ERROR)
  {
    printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
    closesocket(m_Socket);
    WSACleanup();
    exit(1);
  }

  //disable nagle
  char cValue = 1;
  setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, &cValue, sizeof(cValue));
}


C_TCPClientNetwork::~C_TCPClientNetwork()
{

}

unsigned int C_TCPClientNetwork::receivePackets(char* pszRecvBuf)
{
  m_uiResult = C_TCPService::Receive(m_Socket, pszRecvBuf, C_NetPacket::MAX_PACKET_SIZE);

  if (m_uiResult == 0)
  {
    printf("Connection closed\n");

    closesocket(m_Socket);

    WSACleanup();

    exit(1);
  }

  return m_uiResult;
}
