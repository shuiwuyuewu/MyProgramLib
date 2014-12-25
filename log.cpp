#include "stdafx.h"
#include "Log.h"
 
 
Shui::CLog::CLog()
	:m_fp(NULL)
{
	m_fp = fopen("zLog.txt", "w+");
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
	int ret = 0;
 
	time_t now = time(0);
	struct tm* now_tm;
 
	now_tm = gmtime(&now);
	if (now_tm == NULL)
	{
		return 2;
	}
 
	char buf[24];
 
	sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", now_tm->tm_year + 1900, now_tm->tm_mon + 1
		, now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
 
	std::string head(buf);
	head.append(" [");
	head.append(type);
	head.append("]: ");
	head.append(format);
 
	va_list argptr;
	va_start(argptr, format);
	if (m_fp != NULL)
	{
		vfprintf(m_fp, head.c_str(), argptr);
		fprintf(m_fp, "\n");
	}
	else
	{
		ret = 1;
	}
	va_end(argptr);
 
	return ret;
}
