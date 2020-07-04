#include "CPCAPFileReaderProvider.h"
#include "CPCAPFileReader.h"
#include "TraceLogger.h"
#include <algorithm>
using namespace __CT;
using namespace std;
IFileReader* CPCAPFileReaderProvider::getPCAPFileReaderProvider(std::string pFilePath)
{
	TraceLogger("CPCAPFileReaderProvider::getPCAPFileReaderProvider");
	if(!pFilePath.empty())
	{
		LogInfo("FilePath::"+pFilePath);
		string::size_type idx = pFilePath.rfind('.');
		LogInfo("idx::"+idx);
		if(idx != string::npos)
		{
			string lFileExtension = pFilePath.substr(idx+1);
			LogInfo("lFileExtension::"+lFileExtension);
		        transform( lFileExtension.begin(),
				     lFileExtension.end(),
				     lFileExtension.begin(),
					::toupper);	
			LogInfo("lFileExtension::"+lFileExtension);
			if(lFileExtension.compare("PCAP") == 0 )
			{
				CPCAPFileReader *lTmpPtr = new CPCAPFileReader(pFilePath);
				if(lTmpPtr->init() != 1)
					return nullptr;	
				else
					return lTmpPtr;
			}
		}
	}
	return nullptr;
}

