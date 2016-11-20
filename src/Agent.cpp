#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include "../inc/Agent.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"

Agent::Agent(const Config& _config, const PubSubHub* _hub) : m_config(_config.GetConfig())
{
	if(!_hub) 
		throw("nullptr exception");	
	else
		m_hub = (PubSubHub*) _hub;

	//_hub->Subscribe(this);

	m_deque = new SafeDeque<Event*>();
}

Agent::~Agent()
{
	if(m_deque) 
		delete m_deque;
	m_deque = 0;
}

void Agent::Recieve(const Event* _event)
{
	m_deque->Push((Event*) _event);
}

const Event* Agent::GetEvent()
{
	return m_deque->Pop();
}

void Agent::Send(const Event* _event) const
{
	m_hub->Recieve(_event);
}

const PubSubHub* Agent::GetHub() const
{
	return m_hub;
}

string Agent::GetLocation() const
{
	map<string, string>::const_iterator room_it = m_config.find("room");
	map<string, string>::const_iterator floor_it = m_config.find("floor");
	string loc;
	if(floor_it != m_config.end()) loc += (*floor_it).second;
	if(room_it != m_config.end()) loc += (*room_it).second;
	return loc;
}

void Agent::SendEventToHub(const Event* _event)
{
	m_hub->Recieve(_event);
}

void Agent::SubscribeToHub()
{
	m_hub->Subscribe(this);
}

const string& Agent::GetData(const string& _key)
{
	map<string, string>::const_iterator it = m_config.find(_key);
	if(it != m_config.end())
	{
		return (*it).second;
	}
	else
	{
		throw ("no such field");
	}
}



















































