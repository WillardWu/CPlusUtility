#ifndef _X_CRITICAL_SECTION_H_
#define _X_CRITICAL_SECTION_H_

#include "XDefine.h"
#include "XMutex.h"
#include "XNoncopyable.h"

namespace xbase {

////////////////////////////////////////////////////////////////////////////////
// XCritical
////////////////////////////////////////////////////////////////////////////////
class XBASE_API XCritical
//class XBASE_API XCritical : XNonCopyable
{
public:
	XCritical();

	~XCritical();

public:
	void Lock();

	BOOL TryLock();

	void UnLock();

private:
#ifdef __WINDOWS__
	CRITICAL_SECTION m_sCriticalSection;
#endif//__WINDOWS__
#ifdef __GNUC__
	pthread_mutex_t		m_mutex;
#endif//__GNUC__
};


} // namespace xbase

using namespace xbase;

#endif//_X_CRITICAL_SECTION_H_
