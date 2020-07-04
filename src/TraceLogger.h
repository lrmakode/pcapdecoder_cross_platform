#include <iostream>
#include <string>
using namespace std;
namespace __CT
{
	class TraceLogger
	{
	private:
		std::string mFName;
	public:
		TraceLogger(std::string fName)
		{
			mFName = fName;
			cout<<"Entering::"<<fName<<endl;	
		}
		~TraceLogger()
		{
			cout<<"Exiting::"<<mFName<<endl;	
		}
	};
	class Logger
	{
	public:
		static Logger& getInstance()
		{
			static Logger logger;
			return logger;
		}
		void log(string pMessage)
		{
			cout<<pMessage<<endl;
		}
	private:
		Logger()
		{

		}
		~Logger()
		{

		}
	};
   #define LogInfo(lmsg) Logger::getInstance().log(lmsg)
}
