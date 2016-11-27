#include "../inc/Agent.h"
#include "../inc/AgentFactory.h"
#include "../inc/PubSubHub.h"
#include "../inc/AgentLifecycleManager.h"
#include "../inc/Config.h"
#include <vector>
#include <iostream>//for test
#include <csignal>

using namespace std;

AgentLifecycleManager::AgentLifecycleManager(AgentFactory* _factory, PubSubHub* _hub) : m_factory(_factory), m_hub(_hub) 
{}

AgentLifecycleManager::~AgentLifecycleManager()
{}

void AgentLifecycleManager::CreateAgents(const vector<Config>& _configs)
{
	for(vector<Config>::const_iterator it = _configs.begin(); it != _configs.end(); ++it)
	{
		//cout << "AgentLifecycleManager : Agent created. Type: " << (*it).GetData("type") << endl;		
		Agent* agent = 	m_factory->CreateAgent(*it, m_hub);
		//agent->SubscribeToHub();
		m_agents.push_back(agent);
		//agent->SubscribeToHub();
		agent->Run();
	}
}

void AgentLifecycleManager::DestroyAgents()
{
	for(vector<Agent*>::iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		//cout << "Before join" << endl;		
		//raise(SIGINT);
		(*it)->JoinThreads();		
		//cout << "After join" << endl;
		delete *it;
	}
}
