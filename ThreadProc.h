#pragma once

typedef void (*THREADCB)();

class CThreadProc
{
public:
	CThreadProc(void);
	virtual ~CThreadProc(void);

private:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);

public:
	int Start();
	int Stop();
	bool IsRun();
	DWORD GetThreadId();
	void SetCB(THREADCB cb){m_cb = cb;}

protected:
	virtual int Run()
	{
		if (m_cb != NULL)
		{
			(*m_cb)();
		}
		return 0;
	};

private:
	HANDLE m_hThreadQuit;
	HANDLE m_hThread;
	DWORD  m_nThreadId;
	bool   m_bRunning;
	THREADCB m_cb;
};

