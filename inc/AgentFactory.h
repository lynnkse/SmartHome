#ifndef __AGENTFACTORY_H__
#define __AGENTFACTORY_H__


#include <map>

class Agent;
class Config;
class PubSubHub;
class AgentCreator;

class AgentFactory
{
public:
	~AgentFactory();
	static AgentFactory& GetInstance();
	Agent* CreateAgent(const Config& _conf, const PubSubHub* _hub) const;	
	void AddCreator(const string& _name, const AgentCreator* _creator);

private:
	AgentFactory();
	AgentFactory(const AgentFactory& _fact);
	void operator=(const AgentFactory& _fact);
	
	map<string, AgentCreator*> m_creators;
};

#endif
