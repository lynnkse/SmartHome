class Agent;
class PubSubHub;
class Config;
class Deque;
class SafeDeque;
class Config;
class Event;

class ElevatorAgent : Agent
{
public:
	ElevatorAgent(const Config& _config, const PubSubHub& _hub);
	~ElevatorAgent();
	virtual void Recieve();
	
protected:

private:
	void operator=(const Agent& _agnt);
	void ElevatorAgent(const Agent& _agnt);
};
