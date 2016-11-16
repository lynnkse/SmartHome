class Agent;
class PubSubHub;
class Config;
class Deque;
class SafeDeque;
class Config;
class Event;

class TempSensorAgent : Agent
{
public:
	TempSensorAgent(const Config& _config, const PubSubHub& _hub);
	~TempSensorAgent();
	virtual void Recieve();
	
protected:

private:
	void operator=(const Agent& _agnt);
	void TempSensorAgent(const Agent& _agnt);
};
