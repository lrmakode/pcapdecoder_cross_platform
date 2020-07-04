#include "CPCAPFileReader.h"
#include "TraceLogger.h"
#include "CRawPacket.h"
#include <stdio.h>
#include <cstdint>
using namespace std;
using namespace __CT;

typedef struct pcaprec_hdr_s {
        uint32_t ts_sec;         /* timestamp seconds */
        uint32_t ts_usec;        /* timestamp microseconds */
        uint32_t incl_len;       /* number of octets of packet saved in file */
        uint32_t orig_len;       /* actual length of packet */
	void dump()
	{
		printf("pcap header<%d %d %d %d>\n", ts_sec, ts_usec, incl_len, orig_len);
	}
	
} pcaprec_hdr_t;
const uint32_t size_pcaprechdr = sizeof(pcaprec_hdr_t);

CPCAPFileReader::CPCAPFileReader(std::string& pFilePath)
{
	TraceLogger l("CPCAPFileReader::CPCAPFileReader");
	mFilePath = pFilePath;	
	misSwapped = false;
}

unique_ptr<CRawPacket> CPCAPFileReader::getNextPacket()
{
	TraceLogger l("CPCAPFileReader::getNextPacket");
	pcaprec_hdr_t lpcapRecHdr;	
	int32_t lDataRead = fread( &lpcapRecHdr, size_pcaprechdr, 1, mFileHandle);
	cout<<lDataRead <<endl;	
	if( lDataRead < 1 )
		return nullptr;
	lpcapRecHdr.dump();
	uint8_t *ldata = (uint8_t*)malloc(lpcapRecHdr.incl_len);
	lDataRead = fread( ldata, 1, lpcapRecHdr.incl_len, mFileHandle);
	cout<<lDataRead<<"::"<<lpcapRecHdr.incl_len<<endl;
	if( lDataRead != lpcapRecHdr.incl_len)	
		return nullptr;
	LinkLayerType LTT;
	if(mPcapGolbalHdr.network == 1 )
		LTT = LinkLayerType::LINKTYPE_ETH;
	else
		LTT = LinkLayerType::LINKTYPE_NULL;
//	unique_ptr<uint8_t> luptrToRawData = unique_ptr<uint8_t>(ldata);
	unique_ptr<CRawPacket> luptrRawPac(new CRawPacket(std::move(unique_ptr<uint8_t>(ldata)), lDataRead, LTT));	
	
	return luptrRawPac;
}

int32_t CPCAPFileReader::init()
{
	TraceLogger l("CPCAPFileReader::init");
	if(!doesFileExists())
	{
		LogInfo("mFilePath not exist::"+mFilePath);
		return -1;	
	}
	mFileHandle = fopen(mFilePath.c_str(),"r");
	if ( nullptr == mFileHandle)
	{
		return -2;
	}
	int32_t size = sizeof(mPcapGolbalHdr);
	struct pcap_hdr_s ltm;
	int32_t lDataRead = fread( &ltm, size,1, mFileHandle);
	if(lDataRead != 1)
		return -3;
	if( mPcapGolbalHdr.magic_number == 0xd4c3b2a1 || mPcapGolbalHdr.magic_number == 0xa1b2c3d4)
		return -4;
	
	mPcapGolbalHdr = ltm;
	if(mPcapGolbalHdr.magic_number == 0xd4c3b2a1)
		misSwapped = true;
	mPcapGolbalHdr.dump();

	return 1;
}

bool CPCAPFileReader::doesFileExists()
{
	FILE *lFilePtr = nullptr;
	try{
		lFilePtr = fopen(mFilePath.c_str(),"r");
		if(nullptr == lFilePtr)
		{
			LogInfo(mFilePath+"File not exist");
			return false;	
		}
		fclose(lFilePtr);
	}
	catch(std::exception& e)
	{
		LogInfo(e.what());		
		if(nullptr != lFilePtr)
			fclose(lFilePtr);
	}
	LogInfo(mFilePath+"::Exist on disk");
	return true;
}

CPCAPFileReader::~CPCAPFileReader()
{
	TraceLogger l("CPCAPFileReader::~CPCAPFileReader");
}


