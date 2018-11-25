// 2008-02-23 17:06
// XThread.cpp
// guosh
// 线程类实现

#include "XThread.h"

namespace xbase {

///////////////////////////////////////////////////////////////////////////////
// XThread
////////////////////////////////////////////////////////////////////////////////
#ifdef __WINDOWS__
XThread::XThread()
	: m_hThread(NULL)
	, m_uThreadID(0)
	, m_pfThreadProc(NULL)
	, m_pParam(NULL)
	, m_evQuit(TRUE)
{
	// empty
}

XThread::~XThread()
{
	ASSERT(!m_uThreadID && "Need to hand call Join before XThread destruction.");
}

BOOL XThread::Start(PFTHREADPROC pfThreadProc, void *pParam)
{
	Join();

	if (pfThreadProc == NULL)
	{
		m_pfThreadProc = XThread::_Entry;
		m_pParam = this;
	}
	else
	{
		m_pfThreadProc = pfThreadProc;
		m_pParam = pParam;
	}

	unsigned threadID;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, m_pfThreadProc, m_pParam, 0, &threadID);
	if (m_hThread == NULL)
	{
		return FALSE;
	}
	m_uThreadID = (uint64)threadID;

	return TRUE;
}

// 检测退出信号
BOOL XThread::TryWaitQuit(uint32 uMilliseconds)
{
	return m_evQuit.TryWait(uMilliseconds);
}

void XThread::PostStop()
{
	m_evQuit.Set();
	return;
}

void XThread::Exit()
{
	_endthreadex(0);
	return;
}

void XThread::Kill()
{
	TerminateThread(m_hThread, 0);
	return;
}

void XThread::Join()
{
	if (m_uThreadID == 0) return;

	//WaitForSingleObject(m_hThread, INFINITE);
	if (WaitForSingleObject(m_hThread, 5000)==WAIT_TIMEOUT)
	{
		Kill();
	}
	CloseHandle(m_hThread);
	m_hThread = NULL;

	m_uThreadID = 0;
	m_evQuit.Reset();
	return;
}

unsigned XThread::_Entry(void* pParam)
{
	XThread *pThis = static_cast<XThread *>(pParam);
	if (pThis)
	{
		pThis->Entry();
	}
	return 0;
}

// 线程休眠指定毫秒值
void XThread::Sleep(uint32 nMillisecond)
{
	::Sleep(nMillisecond);
	return;
}

// 获取线程自身ID
uint64 XThread::SelfID(void)
{
	return (uint64)GetCurrentThreadId();
}


void XThread:: Entry()
{}
#endif//__WINDOWS__


///////////////////////////////////////////////////////////////////////////////
// XThread
////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
XThread::XThread()
	: m_uThreadID(0)
	, m_pfThreadProc(NULL)
	, m_pParam(NULL)
	, m_evQuit(TRUE)
{
	// empty
}

XThread::~XThread()
{
	ASSERT(!m_uThreadID && "Need to hand call Join before XThread destruction.");
}

BOOL XThread::Start(PFTHREADPROC pfThreadProc, void *pParam)
{
	Join();

	if (pfThreadProc == NULL)
	{
		m_pfThreadProc = XThread::_Entry;
		m_pParam = this;
	}
	else
	{
		m_pfThreadProc = pfThreadProc;
		m_pParam = pParam;
	}

	pthread_t threadID = 0;
	if (0 != pthread_create(&threadID, NULL, m_pfThreadProc, m_pParam))
	{
		return FALSE;
	}
	m_uThreadID = (uint64)threadID;

	return TRUE;
}

// 检测退出信号
BOOL XThread::TryWaitQuit(uint32 uMilliseconds)
{
	return m_evQuit.TryWait(uMilliseconds);
}

void XThread::PostStop()
{
	m_evQuit.Set();
	return;
}

void XThread::Exit()
{
	pthread_exit(0);
	return;
}

void XThread::Kill()
{
	pthread_cancel((pthread_t)m_uThreadID);
	return;
}

void XThread::Join()
{
	if (m_uThreadID == 0) return;

	pthread_join(m_uThreadID, NULL);

	m_uThreadID = 0;
	m_evQuit.Reset();
	return;
}

void* XThread::_Entry(void *pParam)
{
	XThread *pThis = static_cast<XThread *>(pParam);
	if (pThis)
	{
		pThis->Entry();
	}
	return 0;
}


// 线程休眠指定毫秒值
void XThread::Sleep(uint32 nMillisecond)
{
	struct timeval tv;
	tv.tv_sec = nMillisecond / 1000;
	tv.tv_usec = (nMillisecond % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
	return;
}

// 获取线程自身ID
uint64 XThread::SelfID(void)
{
	return (uint64)pthread_self();
}


void XThread:: Entry()
{}
#endif//__GNUC__


//  线程是否退出
BOOL XThread::IsExitThread()
{
	return TryWaitQuit();
}


} // namespace xbase

