#include <string>

#include "C_NetPacket.h"

C_NetPacket::C_NetPacket()
{
  memset(m_szText, 0, 256);
}

C_NetPacket::~C_NetPacket()
{

}

void C_NetPacket::Serialize(char* pData)
{
  memcpy(pData, this, sizeof(C_NetPacket));
}

void C_NetPacket::Deserialize(char* pData)
{
  memcpy(this, pData, sizeof(C_NetPacket));
}
