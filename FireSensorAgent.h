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
	virtual void Recieve();
	
protected:

private:
	void operator=(const Agent& _agnt);
	void FireSensorAgent(const Agent& _agnt);
};
