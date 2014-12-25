#include "stdafx.h"
#include "Log.h"
 
 
Shui::CLog::CLog()
	:m_fp(NULL)
{
	errno_t err = fopen_s(&m_fp, "zLog.txt", "w+");
}
 
 
Shui::CLog::~CLog()
{
	if (m_fp != NULL)
	{
		fclose(m_fp);
		m_fp = NULL;
	}
}
 
Shui::CLog* Shui::CLog::GetInstance()
{
	static CLog log;
	return &log;
}
 
int Shui::CLog::Print(const char* type, const char* format, ...)
{
	CAutoLock l(m_lock);

	int ret = 0;
 
	time_t now = time(0);
	struct tm now_tm;
 
	errno_t err = gmtime_s(&now_tm, &now);
	if (err == EINVAL)
	{
		return 2;
	}
 
	char buf[126];
 
	sprintf_s(buf, "%d-%02d-%02d %02d:%02d:%02d [%s]: %s", now_tm.tm_year + 1900, now_tm.tm_mon + 1
		, now_tm.tm_mday, now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec, type, format);
 
	va_list argptr;
	va_start(argptr, format);
	if (m_fp != NULL)
	{
		vfprintf(m_fp, buf, argptr);
		fprintf(m_fp, "\n");
	}
	else
	{
		ret = 1;
	}
	va_end(argptr);
 
	return ret;
}

