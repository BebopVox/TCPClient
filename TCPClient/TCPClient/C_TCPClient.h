#pragma once

#include "C_NetPacket.h"

class C_TCPClientNetwork;

class C_TCPClient
{
public:
  C_TCPClient();
  ~C_TCPClient();

  void sendActionPackets();
  void update();

private:
  C_TCPClientNetwork* m_Network;
  char m_szData[C_NetPacket::MAX_PACKET_SIZE];

};