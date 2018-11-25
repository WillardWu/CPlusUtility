
#include "Timer.h"
#include <stdio.h>
#include <unistd.h>

#define USE3

#ifdef USE1
Timer g_stTimer1;
static int iCnt =0;
void TimerEvent1(void)
{

	printf("TimerEvent1 %d execute...\n",iCnt++);
	if(iCnt >= 10)
	{
		//执行10次结束
		g_stTimer1.stop();
	}
}
#endif

#ifdef USE2
void TimerEvent2(void)
{

	printf("TimerEvent2 execute...\n");
}

void TimerEvent3(void)
{

	printf("TimerEvent3 execute...\n");
}
#endif


#ifdef USE3
void TimerEventVideo(void*pVideoId)
{
	long iVideoId = (long)pVideoId;
	printf("TimerEventVideo execute id:%ld...\n",iVideoId);
}

void TimerEventAudio(void*pAudioId)
{
	long iAudioId = (long)pAudioId;
	printf("TimerEventAudio execute id:%ld...\n",iAudioId);
}
#endif


int main()
{
#ifdef USE1
	/////////用法1 BEGIN
    g_stTimer1.setEventCallback(TimerEvent1);
	//微秒单位 没过2秒执行一次 执行10次结束
	int64_t i64interval = 2000000;
	g_stTimer1.start(i64interval, true);
	printf("用法1结束\n");
	return 1;
	/////////用法1 END
#endif

#ifdef USE2
	//添加两个执行一次的定时器
	TimerQueue stTimerQueue;
	stTimerQueue.addTimer(TimerEvent2, 6000, false);
	stTimerQueue.addTimer(TimerEvent3, 1000, false);

	//距离最近下一次执行还剩多少时间
	int64_t iTimeRemain = stTimerQueue.getTimeRemaining();
	while(iTimeRemain>0)
	{
		usleep(iTimeRemain*1000);
		stTimerQueue.handleTimerEvent();
		iTimeRemain = stTimerQueue.getTimeRemaining();
	}

	//任务执行完成

	return 1;
#endif

#ifdef USE3
	//实际应用场景 音视频转发时 交替发送音视频 视频帧率25 40ms发送一帧视频
	//音频采用率44100 AAC 一帧时间(1024*1000)/44100=23ms 23ms发送一帧
	TimerQueue stTimerQueue;

	//发送第一帧视频
	printf("Send First Video Frame...\n");
	long iVedioId = 0;
	stTimerQueue.addTimer(TimerEventVideo, 40, true,(void*)iVedioId);
	//发送第一帧视频
	printf("Send First Audio Frame...\n");
	long iAudioId = 1;
	stTimerQueue.addTimer(TimerEventAudio, 23, true,(void*)iAudioId);

	//距离最近下一次执行还剩多少时间
	int64_t iTimeRemain ;
	while(1)
	{
		iTimeRemain = stTimerQueue.getTimeRemaining();
		if(iTimeRemain>0)
		{
			Timer::sleep(iTimeRemain);
		}
		stTimerQueue.handleTimerEvent();
		
	}

	//任务执行完成
	return 1;

#endif




}
