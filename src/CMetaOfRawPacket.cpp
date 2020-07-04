#include "CMetaOfRawPacket.h"
#include <cstdlib>
using namespace __CT;

CMetaOfRawPacket::CMetaOfRawPacket(unique_ptr<CRawPacket> pRawPacket)
{	
	mRawPacket = std::move(pRawPacket);
}

CMetaOfRawPacket::~CMetaOfRawPacket()
{
}
	
