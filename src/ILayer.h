#pragma once
#include "CRawPacket.h"
#include <memory>
namespace __CT
{
	class Layer
	{
		public:
			virtual void parseNextLayer() = 0;			
			virtual ~Layer() = 0;
	};
}
