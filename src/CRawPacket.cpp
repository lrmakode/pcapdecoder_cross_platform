#include "CRawPacket.h"
#include <cstdlib>
using namespace __CT;

CRawPacket::CRawPacket(unique_ptr<uint8_t> pRawData, int pRawDataLen, LinkLayerType pLinkLayerType)
{	
	mRawData = std::move(pRawData);
	mRawDataLen = pRawDataLen;
	mLinkLayerType = pLinkLayerType;
}

const uint8_t* CRawPacket::getRawData() const
{
 	return mRawData.get();
}

int CRawPacket::getRawDataLen() const
{
	return mRawDataLen;
}

const LinkLayerType CRawPacket::getLinkLayerType() const
{
	return mLinkLayerType;
}

CRawPacket::~CRawPacket()
{
}
	
