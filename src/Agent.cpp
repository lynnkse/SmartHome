#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include "../inc/Agent.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"

Agent::Agent(const Config& _config, const PubSubHub* _hub) : m_type(_config.GetType()), m_room(_config.GetRoom()), m_floor(_config.GetFloor()), m_log(_config.GetLog()), m_config(_config.GetConfig())
{
	if(!_hub) 
		throw("nullptr exception");	
	else
		m_hub = (PubSubHub*) _hub;

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
	return m_floor + "|" + m_room;
}

void Agent::SendEventToHub(const Event* _event)
{
	m_hub->Recieve(_event);
}





















































