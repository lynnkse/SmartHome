#ifndef __ELEVATORAGENT_H__
#define __ELEVATORAGENT_H__

#include "../inc/Agent.h"

class PubSubHub;
class Config;
//class Deque;
//class Event;

class ElevatorAgent : public Agent
{
public:
	ElevatorAgent(const Config& _config, const PubSubHub* _hub);
	~ElevatorAgent();
	//virtual void Run();
	
protected:
	virtual string GetLocation() const;
	virtual void ProcessEvents();
	virtual void GenerateEvent();

private:
	void operator=(const Agent& _agnt);
	ElevatorAgent(const Agent& _agnt);
	//virtual void Send(const Event& _event);
	int m_currFloor;

	//thread m_recievingThread;
	//thread m_sendingThread;
};

#endif
