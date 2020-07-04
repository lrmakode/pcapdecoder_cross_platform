#pragma once
#include <stdint.h>
#include <memory>
using namespace std;
namespace __CT
{
	enum LinkLayerType
	{
		LINKTYPE_NULL = 0,
		LINKTYPE_ETH  = 1
	};
	class CRawPacket
	{
		public:
			CRawPacket(std::unique_ptr<uint8_t> pRawData, int pRawDataLen, LinkLayerType pLinkLayerType= LINKTYPE_ETH);
			const uint8_t* getRawData() const;  
			int getRawDataLen() const;  
			const LinkLayerType getLinkLayerType() const;			
			virtual ~CRawPacket();
		private:
			std::unique_ptr<uint8_t> mRawData;
			int mRawDataLen;
			LinkLayerType mLinkLayerType;
	};
}

