#ifndef __ELEVATORAGENT_H__
#define __ELEVATORAGENT_H__

#include "../inc/Agent.h"

class PubSubHub;
class Config;
class Deque;
class Config;
class Event;
//template <class Event*>
//class SafeDeque;


class ElevatorAgent : public Agent
{
public:
	ElevatorAgent(const Config& _config, const PubSubHub* _hub);
	~ElevatorAgent();
	
protected:
	virtual string GetLocation() const;

private:
	void operator=(const Agent& _agnt);
	ElevatorAgent(const Agent& _agnt);
	//virtual void Send(const Event& _event);
	virtual void Run();
	void ProcessEvents();
	void GenerateEvent();
	int m_currFloor;

	thread m_recievingThread;
	thread m_sendingThread;
	//pthread_t m_recievingThread;
	//pthread_t m_sendingThread;
};

#endif
