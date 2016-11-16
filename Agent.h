class PubSubHub;
class Config;
class Deque;
class SafeDeque;
class Config;
class Event;

class Agent
{
public:
	Agent(const Config& _config, const PubSubHub& _hub);
	~Agent();
	virtual void Recieve(const Event& _event) = 0;
	
protected:
	//GetHub
	//GetQueue
	//GetConfig

private:
	void operator=(const Agent& _agnt);
	void Agent(const Agent& _agnt);
	virtual void Send();//TODO !!!!
	
	PubSubHub* m_hub;
	SafeDeque* m_deque;
	string m_type;
	string m_room;
	string m_floor;
    string m_log;
	string m_config;
};
