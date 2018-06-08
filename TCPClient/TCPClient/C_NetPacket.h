#pragma once

class C_NetPacket
{
public:
  static const int MAX_PACKET_SIZE = 1000000;

  enum PacketTypes
  {
    Init = 0,
    ActionEvent = 1,
  };

  C_NetPacket();
  ~C_NetPacket();

  void Serialize(char* pData);
  void Deserialize(char* pData);

  unsigned int m_uiType;
  char m_szText[256];
};
