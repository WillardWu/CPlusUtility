
// windows下的事件概念和unix下的条件变量概念

#pragma once

#ifndef _X_EVENT_H_
#define _X_EVENT_H_

#include "XDefine.h"
#include "XCritical.h"
#include "XNoncopyable.h"

namespace xbase {

////////////////////////////////////////////////////////////////////////////////
// XEvent
////////////////////////////////////////////////////////////////////////////////
class XBASE_API XEvent 
//class XBASE_API XEvent : XNonCopyable
{
public:
	// 默认为自动重置锁
	XEvent(BOOL bManualReset = FALSE);

	~XEvent();

public:
	void Set();

	void Reset();

	void Wait();

	BOOL TryWait(uint32 msec/*millisecond*/ = 0);

private:
#ifdef __WINDOWS__
	HANDLE				m_handle;
#endif//__WINDOWS__
#ifdef __GNUC__
	pthread_cond_t		m_handle;			// 条件变量
	volatile BOOL		m_flag;				// 信标
	pthread_mutex_t		m_mutex;			// 锁
#endif//__GNUC__

	BOOL				m_bManualReset;		// 是否手工重置
};

} // namespace xbase

using namespace xbase;

#endif//_X_EVENT_H_
