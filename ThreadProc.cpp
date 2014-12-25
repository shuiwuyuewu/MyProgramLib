#include "StdAfx.h"
#include "ThreadProc.h"


CThreadProc::CThreadProc(void)
	:m_hThreadQuit(NULL)
	,m_hThread(NULL)
	,m_nThreadId(0)
	,m_bRunning(false)
{
}


CThreadProc::~CThreadProc(void)
{
	if (m_bRunning)
	{
		Stop();
	}
}

DWORD WINAPI CThreadProc::ThreadProc(LPVOID lpParameter)
{
	CThreadProc* pThis = reinterpret_cast<CThreadProc*>(lpParameter);

	OutputDebugString(_T("Enter ThreadProc\n"));
	while(1)
	{
		DWORD ret = WaitForSingleObject(pThis->m_hThreadQuit, 1);
		if ( ret == WAIT_OBJECT_0)
		{
			break;
		}
		else if (ret == WAIT_TIMEOUT)
		{
			//OutputDebugString(_T("Enter Run\n"));
			pThis->Run();
			//OutputDebugString(_T("Leave Run\n"));
		}
		else
		{
			OutputDebugString(_T("WaitForSingleObject error\n"));
			break;
		}
	}
	OutputDebugString(_T("Leave ThreadProc\n"));
	return 0;
}

int CThreadProc::Start()
{
	if (m_bRunning)
	{
		OutputDebugString(_T("Thread Already running\n"));
		return -2;
	}

	m_hThreadQuit = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (m_hThreadQuit == NULL)
	{
		OutputDebugString(_T("CreateEvent error\n"));
		return -1;
	}

	m_hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &m_nThreadId);

	if (m_hThread == NULL)
	{
		OutputDebugString(_T("CreateThread error\n"));
		CloseHandle(m_hThreadQuit);
		m_hThreadQuit = NULL;
		m_nThreadId   = 0;
		return -2;
	}

	m_bRunning = true;
	return 0;
}

int CThreadProc::Stop()
{
	if (!m_bRunning)
	{
		OutputDebugString(_T("Thread already running\n"));
		return -1;
	}

	SetEvent(m_hThreadQuit);
	WaitForSingleObject(m_hThread, INFINITE);

	CloseHandle(m_hThread);
	CloseHandle(m_hThreadQuit);
	m_hThread     = NULL;
	m_hThreadQuit = NULL;
	m_nThreadId   = 0;
	m_bRunning    = false;

	return 0;
}

bool CThreadProc::IsRun()
{
	return m_bRunning;
}

DWORD CThreadProc::GetThreadId()
{
	return m_nThreadId;
}
