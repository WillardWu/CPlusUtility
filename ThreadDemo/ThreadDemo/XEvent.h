
// windows�µ��¼������unix�µ�������������

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
	// Ĭ��Ϊ�Զ�������
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
	pthread_cond_t		m_handle;			// ��������
	volatile BOOL		m_flag;				// �ű�
	pthread_mutex_t		m_mutex;			// ��
#endif//__GNUC__

	BOOL				m_bManualReset;		// �Ƿ��ֹ�����
};

} // namespace xbase

using namespace xbase;

#endif//_X_EVENT_H_
