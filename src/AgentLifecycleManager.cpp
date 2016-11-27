#include "../inc/Agent.h"
#include "../inc/AgentFactory.h"
#include "../inc/PubSubHub.h"
#include "../inc/AgentLifecycleManager.h"
#include "../inc/Config.h"
#include <vector>
#include <iostream>
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
		Agent* agent = 	m_factory->CreateAgent(*it, m_hub);
		m_agents.push_back(agent);
		agent->Run();
	}
}

void AgentLifecycleManager::DestroyAgents()
{
	for(vector<Agent*>::iterator it = m_agents.begin(); it != m_agents.end(); ++it)
	{
		(*it)->JoinThreads();		
		delete *it;
	}
}
