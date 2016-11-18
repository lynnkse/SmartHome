#include <vector>

class PubSubHub;

using namespace std;

class AgentFactory;
class Agent;
class Config;

class AgentLifecycleManager
{
public:
	AgentLifecycleManager(AgentFactory* _factory, PubSubHub* _hub);
	~AgentLifecycleManager();
	void CreateAgents(const vector<Config>& _configs);
	void DestroyAgents();

private:	
	void operator=(const AgentLifecycleManager& _p);
	AgentLifecycleManager(const AgentLifecycleManager& _p);

	AgentFactory* m_factory;
	PubSubHub* m_hub;
	vector<Agent*> m_agents;
};
