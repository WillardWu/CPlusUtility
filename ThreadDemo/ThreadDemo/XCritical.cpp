
#include "XCritical.h"

namespace xbase {

////////////////////////////////////////////////////////////////////////////////
// XCritical
////////////////////////////////////////////////////////////////////////////////
#ifdef __WINDOWS__
XCritical::XCritical()
{
	InitializeCriticalSection(&m_sCriticalSection);
}

XCritical::~XCritical()
{
	DeleteCriticalSection(&m_sCriticalSection);
}

void XCritical::Lock()
{
	EnterCriticalSection(&m_sCriticalSection);
}

BOOL XCritical::TryLock()
{
	return TryEnterCriticalSection(&m_sCriticalSection);
}

void XCritical::UnLock()
{
	LeaveCriticalSection(&m_sCriticalSection);
}
#endif //__WINDOWS__

////////////////////////////////////////////////////////////////////////////////
// XCritical
////////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__
XCritical::XCritical()
{
	int ret = -1;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); // PTHREAD_MUTEX_RECURSIVE_NP
	ASSERT(0 == ret);
	ret = pthread_mutex_init(&m_mutex, &attr);
	ASSERT(0 == ret);
	ret = pthread_mutexattr_destroy(&attr);
	ASSERT(0 == ret);
	ret = 0;
}

XCritical::~XCritical()
{
	pthread_mutex_destroy(&m_mutex);
}

void XCritical::Lock()
{
	pthread_mutex_lock(&m_mutex);
}

BOOL XCritical::TryLock()
{
	return (BOOL)(0 == pthread_mutex_trylock(&m_mutex));
}

void XCritical::UnLock()
{
	int ret = pthread_mutex_unlock(&m_mutex);
	ASSERT(!ret && "the calling thread does not own the mutex.");
	ret = 0;
}
#endif //__GNUC__

} // namespace xbase

