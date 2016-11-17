class Config;

class AgentCreator
{
public:
	AgentCreator(){};
	virtual ~AgentCreator(){} = 0;
	Agent* Create(const Config& _conf, const PubSubHub* _hub) const = 0;
	
private:
	void operator=(const AgentCreator& _crtr);
	AgentCreator(const AgentCreator& _crtr);
};
