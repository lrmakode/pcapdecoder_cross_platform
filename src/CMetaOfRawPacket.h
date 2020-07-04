#pragma once
#include <stdint.h>
#include "CRawPacket.h"
#include "ILayer.h"
namespace __CT
{
	class CMetaOfRawPacket
	{
		public:
			CMetaOfRawPacket(unique_ptr<CRawPacket> pRawPacket);
			virtual ~CMetaOfRawPacket();
		private:
			unique_ptr<CRawPacket> mRawPacket;
		  	shared_ptr<Layer> mNextLayer;	
		  	shared_ptr<Layer> mPrevLayer;	
	};
}

