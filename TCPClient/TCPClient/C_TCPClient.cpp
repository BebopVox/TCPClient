#include <iostream>

#include "C_TCPClientNetwork.h"
#include "C_TCPService.h"

#include "C_TCPClient.h"

using namespace std;

C_TCPClient::C_TCPClient()
{
  m_Network = new C_TCPClientNetwork();

  // send init packet
  const unsigned int uiPacketSize = sizeof(C_NetPacket);
  char szPacketData[uiPacketSize];

  C_NetPacket packet;
  packet.m_uiType = C_NetPacket::PacketTypes::Init;

  packet.Serialize(szPacketData);

  C_TCPService::Send(m_Network->m_Socket, szPacketData, uiPacketSize);
}

C_TCPClient::~C_TCPClient()
{

}

void C_TCPClient::sendActionPackets()
{
  // send action packet
  const unsigned int uiPacketSize = sizeof(C_NetPacket);
  char szPacketData[uiPacketSize];

  C_NetPacket packet;
  packet.m_uiType = C_NetPacket::PacketTypes::ActionEvent;

  packet.Serialize(szPacketData);

  C_TCPService::Send(m_Network->m_Socket, szPacketData, uiPacketSize);
}

void C_TCPClient::update()
{
  C_NetPacket packet;
  int iDataLength = m_Network->receivePackets(m_szData);

  if (iDataLength < 1)
  {
    //no data recieved
    return;
  }

  for (unsigned int i = 0; i < (unsigned int)iDataLength; i += sizeof(C_NetPacket))
  {
    packet.Deserialize(&(m_szData[i]));

    switch (packet.m_uiType)
    {
      case C_NetPacket::PacketTypes::ActionEvent:
      {
        cout << "client: received action event packet from server: " << packet.m_szText << endl;
        sendActionPackets();
        break;
      }
      default:
      {
        cout << "client: error in packet types" << endl;
        break;
      }
    }
  }
}
