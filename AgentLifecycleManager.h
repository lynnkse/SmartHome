#include <vector>

using namespace std;

class AgentFactory;
class Agent;
class Config;

class AgentLifecycleManager
{
public:
	AgentLifecycleManager(const AgentFactory& _factory);
	~AgentLifecycleManager();
	void CreateAgents(const vector<Config>& _configs);
	void DestroyAgents();

private:	
	void operator=(const AgentLifecycleManager& _p);
	void AgentLifecycleManager(const AgentLifecycleManager& _p);
	AgentFactory* m_factory;
	vector<Agent> m_agents;
};
