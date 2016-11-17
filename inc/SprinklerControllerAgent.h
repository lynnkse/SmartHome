class Agent;
class PubSubHub;
class Config;
class Deque;
class SafeDeque;
class Config;
class Event;

class SprinklerControllerAgent : Agent
{
public:
	SprinklerControllerAgent(const Config& _config, const PubSubHub& _hub);
	~SprinklerControllerAgent();
	virtual void Recieve(const Event& _event);
	
protected:

private:
	void operator=(const Agent& _agnt);
	void SprinklerControllerAgent(const Agent& _agnt);
	virtual void Send(const Event& _event);
	virtual Run();
};
