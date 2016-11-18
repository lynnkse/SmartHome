#include "../inc/AgentCreator.h"
#include "../inc/Agent.h"
#include "../inc/AgentFactory.h"
#include "../inc/Config.h"

AgentFactory::AgentFactory() {}

AgentFactory::~AgentFactory() {}

AgentFactory& AgentFactory::GetInstance() 
{ 
	static AgentFactory agentFactory; 
	return agentFactory; 
}	

void AgentFactory::AddCreator(const string& _name, const AgentCreator* _creator)
{
	m_creators[_name] = (AgentCreator*)_creator;
}

Agent* AgentFactory::CreateAgent(const Config& _conf, const PubSubHub* _hub) const
{
	map<string, AgentCreator*>::const_iterator it = m_creators.find(_conf.GetType());
	if(it != m_creators.end())
	{
		return (it->second)->Create(_conf, _hub);
	}
	else
	{
		return 0;
	}
}	


