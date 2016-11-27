#ifndef __FIRESENSORAGENT_H__
#define __FIRESENSORAGENT_H__

class Agent;
class PubSubHub;
class Config;
class Deque;
class SafeDeque;
class Config;
class Event;

class FireSensorAgent : Agent
{
public:
	FireSensorAgent(const Config& _config, const PubSubHub& _hub);
	~FireSensorAgent();
	virtual void Recieve(const Event& _event);
	
protected:

private:
	void operator=(const Agent& _agnt);
	void FireSensorAgent(const Agent& _agnt);
	virtual void Send(const Event& _event);
	virtual Run();
};

#endif
