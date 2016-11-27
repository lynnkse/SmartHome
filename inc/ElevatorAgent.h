#ifndef __ELEVATORAGENT_H__
#define __ELEVATORAGENT_H__

#include "../inc/Agent.h"

class PubSubHub;
class Config;

class ElevatorAgent : public Agent
{
public:
	ElevatorAgent(const Config& _config, const PubSubHub* _hub);
	~ElevatorAgent();
	
protected:
	virtual string GetLocation() const;
	virtual void ProcessEvents();
	virtual void GenerateEvent();

private:
	void operator=(const Agent& _agnt);
	ElevatorAgent(const Agent& _agnt);
	int m_currFloor;
};

#endif
