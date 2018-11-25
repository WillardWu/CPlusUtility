
// �߳���ʵ��


#pragma once

#ifndef _X_THREAD_H_
#define _X_THREAD_H_

#include "XDefine.h"
#include "XEvent.h"
#include "XNoncopyable.h"

namespace xbase {

#ifdef __WINDOWS__
	typedef unsigned (XAPI *PFTHREADPROC)(void* pParam);
#endif//__WINDOWS__
#ifdef __GNUC__
	typedef void* (XAPI *PFTHREADPROC)(void* pParam);
#endif//__GNUC__

///////////////////////////////////////////////////////////////////////////////
// XThread
////////////////////////////////////////////////////////////////////////////////
class XBASE_API XThread 
{
public:
	XThread();

	virtual ~XThread();

public:
	virtual BOOL Start(PFTHREADPROC pfThreadProc = NULL, void *pParam = NULL);

	// ����˳��ź�
	virtual BOOL TryWaitQuit(uint32 uMilliseconds = 0);

	//  �߳��Ƿ��˳�
	virtual BOOL IsExitThread();

	// ����ֹͣ����
	virtual void PostStop();

	// �ȴ��߳̽���,������Դ
	virtual void Join();

	// ɱ���߳�(������ʹ��,��ʹ��PostStop��֪ͨ�߳̽���)
	void Kill();

	// ��ȡ�߳�ID
	uint64 ThreadID() { return m_uThreadID; };

public:
	// ��ȡ���߳�ID
	static uint64 SelfID();

	// �߳�����ָ������ֵ
	static void Sleep(uint32 nMillisecond);

protected:
	virtual void Entry() ;

	// �߳����ѽ���(������ʹ��,��ֱ��return�˳��߳�ִ�к���)
	void Exit();

private:
#ifdef __WINDOWS__
	static unsigned XAPI _Entry(void* pParam);
	HANDLE				m_hThread;
#endif//__WINDOWS__
#ifdef __GNUC__
	static void* XAPI _Entry(void *pParam);
#endif//__GNUC__

private:
	uint64				m_uThreadID;
	PFTHREADPROC		m_pfThreadProc;
	void				*m_pParam;

	XEvent				m_evQuit;		// �������ʹ���ֹ������¼�
};

} // namespace xbase

using namespace xbase;

#endif//_X_THREAD_H_
