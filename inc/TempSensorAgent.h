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
	virtual void Recieve(const Event& _event);
	
protected:

private:
	void operator=(const Agent& _agnt);
	void TempSensorAgent(const Agent& _agnt);
	virtual void Send(const Event& _event);
	virtual Run();
};
