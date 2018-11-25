
// 线程类实现


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

	// 检测退出信号
	virtual BOOL TryWaitQuit(uint32 uMilliseconds = 0);

	//  线程是否退出
	virtual BOOL IsExitThread();

	// 发送停止命令
	virtual void PostStop();

	// 等待线程结束,回收资源
	virtual void Join();

	// 杀死线程(不建议使用,可使用PostStop来通知线程结束)
	void Kill();

	// 获取线程ID
	uint64 ThreadID() { return m_uThreadID; };

public:
	// 获取本线程ID
	static uint64 SelfID();

	// 线程休眠指定毫秒值
	static void Sleep(uint32 nMillisecond);

protected:
	virtual void Entry() ;

	// 线程自已结束(不建议使用,可直接return退出线程执行函数)
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

	XEvent				m_evQuit;		// 这里必须使用手工重设事件
};

} // namespace xbase

using namespace xbase;

#endif//_X_THREAD_H_
