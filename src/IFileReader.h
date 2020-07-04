#pragma once
#include "CRawPacket.h"
#include <memory>
namespace __CT
{
	class IFileReader
	{
		public:
			virtual std::unique_ptr<CRawPacket> getNextPacket() = 0;			
			virtual ~IFileReader() = 0;
	};
}
