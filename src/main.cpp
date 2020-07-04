#include<iostream>
#include <cstdlib>
#include "CPCAPFileReaderProvider.h"
#include "TraceLogger.h"
#include "CMetaOfRawPacket.h"
using namespace __CT;
using namespace std;
int main(int argc, char **argv)
{
   std::cout<<"Pcap Decoder .....0.0 "<<argc<<std::endl;
   if(argc < 2)
   {
	cout<<"Usage::./decoder <pcapfilepath>"	<<endl;
	return -1;
   }
   string lPcapFile = argv[1];
   unique_ptr<IFileReader> lPCAPFileReader = unique_ptr<IFileReader>(CPCAPFileReaderProvider::getPCAPFileReaderProvider(lPcapFile));
   if(nullptr == lPCAPFileReader)
   {
	cout<<"Something went wrong!"<<endl;
	return -1;
   }
   unique_ptr<CRawPacket> luptrRawPacket = lPCAPFileReader->getNextPacket();
   int idx = 0;
   while(nullptr !=luptrRawPacket) 
   {
	idx++;
	unique_ptr<CMetaOfRawPacket> luptrMetaOfRawPacket(new CMetaOfRawPacket(std::move(luptrRawPacket)));
	luptrRawPacket= lPCAPFileReader->getNextPacket();
   }
   cout<<"No of Packets Read:" << idx <<endl;
	
   return 0;
}
