#include "stdafx.h"

#pragma once

class CSimpleLock
{
public:

	CSimpleLock()
	{
		InitializeCriticalSection(&m_cs);
	}
	 
	void Lock()
	{
		EnterCriticalSection(&m_cs);
	}

	void Unlock()
	{
		LeaveCriticalSection(&m_cs);
	}

	BOOL TryLock()
	{
		TryEnterCriticalSection(&m_cs);
	}

	~CSimpleLock()
	{
		DeleteCriticalSection(&m_cs);
	}

private:
	CRITICAL_SECTION m_cs;
};

class CAutoLock
{
public:
	CAutoLock(CSimpleLock& l)
		:m_l(l)
	{
		m_l.Lock();
	}

	~CAutoLock()
	{
		m_l.Unlock();
	}

private:
	CSimpleLock& m_l;
};