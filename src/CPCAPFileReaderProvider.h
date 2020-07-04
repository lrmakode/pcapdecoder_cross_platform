#include "IFileReader.h"
#include <string>
namespace __CT
{
	class CPCAPFileReaderProvider
	{	
		public:
			static IFileReader* getPCAPFileReaderProvider(std::string filePath);
	};
}




