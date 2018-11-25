// 2008-02-23
// Xmutex.cpp
// guosh
// »¥³âËø(²»ÔÊÐíµÝ¹éËø)

#include "XMutex.h"

namespace xbase {

////////////////////////////////////////////////////////////////////////////////
// XMutex
////////////////////////////////////////////////////////////////////////////////
#ifdef __WINDOWS__
XMutex::XMutex()
{
	m_mutex = CreateMutex(NULL, FALSE, NULL);
	ASSERT(m_mutex != NULL);
}

XMutex::~XMutex()
{
	CloseHandle(m_mutex);
}

void XMutex::Lock()
{
	DWORD ret = ::WaitForSingleObject(m_mutex, INFINITE);
	ASSERT(ret == WAIT_OBJECT_0);
	ret = 0;
}

BOOL XMutex::TryLock()
{
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_mutex, 0))
	{
		return TRUE;
	}
	return FALSE;
}

void XMutex::UnLock()
{
	BOOL ret = ::ReleaseMutex(m_mutex);
	ASSERT(ret);
	ret = TRUE;
}
#endif//__WINDOWS__


////////////////////////////////////////////////////////////////////////////////
// XMutex
////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
XMutex::XMutex()
{
	int ret = -1;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK); // PTHREAD_MUTEX_ERRORCHECK_NP
	ASSERT(0 == ret);
	ret = pthread_mutex_init(&m_mutex, &attr);
	ASSERT(0 == ret);
	ret = pthread_mutexattr_destroy(&attr);
	ASSERT(0 == ret);
	ret = 0;
}

XMutex::~XMutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void XMutex::Lock()
{
	int ret = pthread_mutex_lock(&m_mutex);
	ASSERT(!ret && "the mutex is already locked by the calling thread.");
	ret = 0;
}

BOOL XMutex::TryLock()
{
	return (BOOL)(0 == pthread_mutex_trylock(&m_mutex));
}

void XMutex::UnLock()
{
	int ret = pthread_mutex_unlock(&m_mutex);
	ASSERT(!ret && "the calling thread does not own the mutex.");
	ret = 0;
}
#endif//__GNUC__

} // namespace xbase

