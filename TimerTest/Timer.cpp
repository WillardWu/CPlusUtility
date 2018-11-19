#include "Timer.h"
#include <iostream>


using namespace std;
using namespace std::chrono;

TimerId TimerQueue::addTimer(const TimerEvent& event, uint32_t ms, bool repeat,void*pUser)
{
    std::lock_guard<std::mutex> locker(_mutex);

    int64_t timeoutPoint = getTimeNow();
    TimerId timerId = {timeoutPoint+ms, ++_lastTimerId};
    //相当new shared_ptr
    auto timer = make_shared<Timer>(event, ms, repeat,pUser);

    timer->setNextTimeout(timeoutPoint);

    if(repeat)
    {
    	//c++11 中添加emplace 和insert 区别时，插入不需要构造临时变量
    	//参考下面 insert
        _repeatTimers.emplace(timerId.second, timer);
    }

    _timers.insert(std::pair<TimerId,std::shared_ptr<Timer>>(timerId, std::move(timer)));

    return timerId;
}

void TimerQueue::removeTimer(TimerId timerId)
{
    std::lock_guard<std::mutex> locker(_mutex);

    auto iter = _repeatTimers.find(timerId.second);	
    if(iter != _repeatTimers.end())
    {
        TimerId t = {iter->second->getNextTimeout(), timerId.second};
        _repeatTimers.erase(iter);
        _timers.erase(t);		
    }
    else
    {
        _timers.erase(timerId);
    }
}

int64_t TimerQueue::getTimeNow()
{	
    auto timePoint = steady_clock::now();	
    return duration_cast<milliseconds>(timePoint.time_since_epoch()).count();	
}

int64_t TimerQueue::getTimeRemaining()
{	
    std::lock_guard<std::mutex> locker(_mutex);

    if(_timers.empty())
     return -1;

    //因为MAP会自动排序 所以每次所有定时任务 都是按照时间先后排列好的
    int64_t ms = _timers.begin()->first.first - getTimeNow();
    if(ms <= 0)
        return 0; 

    return ms;
}

void TimerQueue::handleTimerEvent()
{
    if(!_timers.empty() || !_repeatTimers.empty())
    {
        std::lock_guard<std::mutex> locker(_mutex);

        int64_t timePoint = getTimeNow();
        while(!_timers.empty() && _timers.begin()->first.first<=timePoint)
        {	
            _timers.begin()->second->eventCallback(_timers.begin()->second->_pUser);
            if(_timers.begin()->second->isRepeat())
            {
                _timers.begin()->second->setNextTimeout(timePoint);
                TimerId t = {_timers.begin()->second->getNextTimeout(), _timers.begin()->first.second};		
                auto timerPtr = std::move(_timers.begin()->second);			
                _timers.erase(_timers.begin());
                _timers.insert(std::pair<TimerId,std::shared_ptr<Timer>>(t, std::move(timerPtr)));

                //_timers.insert(std::pair<TimerId,std::shared_ptr<Timer>>(timerId, std::move(timer)));
            }
            else		
            {
                _timers.erase(_timers.begin());
            }
        }	
    }
}

