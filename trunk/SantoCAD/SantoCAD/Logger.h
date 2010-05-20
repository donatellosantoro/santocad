#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
using namespace std;

class Logger{
	public:
		static const int LOG_DEBUG	= 0;
		static const int LOG_INFO	= 1;
		static const int LOG_ERROR	= 2;

		static int getLoggerLevel(){
			return LOG_ERROR;            // <-- Impostare qui il livello di logging
		}

		static void debug(string s){
			if(getLoggerLevel() <= LOG_DEBUG)
			cout << "Debug: " << s << endl;
		}

		static void debug(string s, char* c){
			if(getLoggerLevel() <= LOG_DEBUG)
			cout << "Debug: " << s << c << endl;
		}

		static void debug(string s, double d){
			if(getLoggerLevel() <= LOG_DEBUG)
			cout << "Debug: " << s << d << endl;
		}

		static void debug(string s1, double d1,string s2, double d2){
			if(getLoggerLevel() <= LOG_DEBUG)
			cout << "Debug: " << s1 << d1 << s2 << d2 << endl;
		}

		static void info(string s){
			if(getLoggerLevel() <= LOG_INFO)
			cout << "Info: " << s << endl;
		}

		static void info(string s, char* c){
			if(getLoggerLevel() <= LOG_INFO)
			cout << "Info: " << s << c << endl;
		}

		static void info(string s, double d){
			if(getLoggerLevel() <= LOG_INFO)
			cout << "Info: " << s << d << endl;
		}

		static void info(string s1, double d1,string s2, double d2){
			if(getLoggerLevel() <= LOG_INFO)
			cout << "Info: " << s1 << d1 << s2 << d2 << endl;
		}

		static void error(string s){
			if(getLoggerLevel() <= LOG_ERROR)
			cout << "Error: " << s << endl;
		}

		static void error(string s, double d){
			if(getLoggerLevel() <= LOG_ERROR)
			cout << "Error: " << s << d << endl;
		}

		static void error(string s, char* c){
			if(getLoggerLevel() <= LOG_ERROR)
			cout << "Error: " << s << c << endl;
		}

		static void error(string s1, double d1,string s2, double d2){
			if(getLoggerLevel() <= LOG_ERROR)
			cout << "Error: " << s1 << d1 << s2 << d2 << endl;
		}
};

#endif
