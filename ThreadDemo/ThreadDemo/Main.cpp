#pragma once
#pragma execution_character_set("utf-8")

#include "XThread.h"

#ifdef __WINDOWS__
unsigned XAPI Thread1Handle(void* pParam)
#endif//__WINDOWS__
#ifdef __GNUC__
void* XAPI Thread1Handle(void* pParam)
#endif//__GNUC__
{
	int iCnt =0;
	XThread* pThread = (XThread*)pParam;
	//或者采用阻塞版本TryWaitQuit(uint32)
	while(!pThread->IsExitThread())
	{
		printf("线程:%lld 运行%d\n",XThread::SelfID(),iCnt++);
		XThread::Sleep(50);
	}
	printf("线程:%ld 运行结束\n",XThread::SelfID());
	return 0;
}

class MyThread:public XThread
{
public:
	//派生类中实现线程处理函数
protected:
	void Entry()
	{
		while(!TryWaitQuit(10))
		{
			printf("MyThread Test\n");
		}

		printf("线程:%ld 运行结束\n",XThread::SelfID());
		
	}
};



int main()
{
	{

		//方法一 直接定义类对象使用
		XThread Thread1;
		Thread1.Start(Thread1Handle,&Thread1);
		XThread::Sleep(1000);
		Thread1.PostStop();
		Thread1.Join();

	}

	//方法二 采用继承的方式
	{
		MyThread Thread2;
		Thread2.Start();

		MyThread::Sleep(1000);

		Thread2.PostStop();
		Thread2.Join();


	
	
	}


	system("PAUSE");

	return 1;
}