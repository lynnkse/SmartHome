class Agent;
class Config;
class PubSubHub;

class AgentFactory
{
public:
	~AgentFactory(){};
	static AgentFactory& GetInstance() { static AgentFactory agentFactory; return agentFactory; }	
	Agent* CreateAgent(cost Config& _conf, const PubSubHub* _hub) config;	

private:
	AgentFactory(){};
	AgentFactory(const AgentFactory& _fact);
	void operator=(const AgentFactory& _fact);
};

