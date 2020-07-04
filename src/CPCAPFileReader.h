#pragma once
#include "IFileReader.h"
#include <string>
namespace __CT
{

	typedef struct pcap_hdr_s {
        	uint32_t magic_number;   /* magic number */
 	        uint16_t version_major;  /* major version number */
	        uint16_t version_minor;  /* minor version number */
	        int32_t thiszone;       /* GMT to local correction */
	        uint32_t sigfigs;        /* accuracy of timestamps */
	        uint32_t snaplen;        /* max length of captured packets, in octets */
	        uint32_t network;        /* data link type */
		void dump()
		{
			printf("global header<%#010x %d %d %d %d %d %d>\n", magic_number, version_major, version_minor, thiszone, sigfigs, snaplen, network);
		}
	} pcap_hdr_t;
	


	class CPCAPFileReader : public IFileReader
	{
		public:
			CPCAPFileReader(std::string& pFileString);
			std::unique_ptr<CRawPacket> getNextPacket();			
			int32_t init();
			~CPCAPFileReader();
		private:
			bool doesFileExists();
			std::string mFilePath;	
			FILE *mFileHandle;
			pcap_hdr_t mPcapGolbalHdr;
			bool misSwapped;

	};
}
