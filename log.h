#pragma once
 
#include <cstdio>
#include <ctime>
#include "SimpleLock.h"

#define DEBUG_S(fmt,...) { Shui::CLog::GetInstance()->Print("DEBUG", fmt, __VA_ARGS__); }while(0)
#define INFO_S(fmt,...) { Shui::CLog::GetInstance()->Print("INFO", fmt, __VA_ARGS__); }while(0)
#define ERROR_S(fmt,...) { Shui::CLog::GetInstance()->Print("ERROR", fmt, __VA_ARGS__); }while(0)
 
namespace Shui
{
	class CLog
	{
	public:
		~CLog();
 
	public:
		static CLog* GetInstance();
 
		int Print(const char* type, const char* format, ...);
 
	private:
		CLog();
 
	private:
		FILE* m_fp;
		CSimpleLock m_lock;
	};
}
