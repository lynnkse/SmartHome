class Agent;
class PubSubHub;
class Config;
class Deque;
class SafeDeque;
class Config;
class Event;

class HVACcontrollerAgent : Agent
{
public:
	HVACcontrollerAgent(const Config& _config, const PubSubHub& _hub);
	~HVACcontrollerAgent();
	virtual void Recieve();
	
protected:

private:
	void operator=(const Agent& _agnt);
	void HVACcontrollerAgent(const Agent& _agnt);
};