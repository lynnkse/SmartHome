#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include "../inc/Agent.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"
#include <iostream>
#include <algorithm>
#include "../inc/Tokenizer_t.h"
#include "../inc/logmngr.h"

using namespace std;

bool Agent::m_isAlive = true;

Agent::Agent(const Config& _config, const PubSubHub* _hub, bool _isController) : m_config(_config.GetConfig()), m_isController(_isController)
{
	Zlog* z = ZlogGet("mod1");
	if(!_hub) 
		{	
			ZLOG_SEND(z, LOG_TRACE, "Hub is NULL pointer ",1);			
			throw("nullptr exception");	
		}	
	else
		m_hub = (PubSubHub*) _hub;
	
	m_itSet = false;

	Tokenizer_t t;

	m_configTokens = t.GetStringTokens(m_config["config"]); 

	vector<string>::iterator it = find(m_configTokens.begin(), m_configTokens.end(), "From");
	if(it != m_configTokens.end())
	{
		++it;
		SetConfig("From", *it);
	}
	else
	{
		SetConfig("From", "All");
	}

	vector<string>::iterator iter = find(m_configTokens.begin(), m_configTokens.end(), "Event");
	if(iter != m_configTokens.end())
	{
		++iter;
		SetConfig("Event", *iter);
	}


	m_deque = new SafeDeque<Event*>();
	ZLOG_SEND(z, LOG_TRACE, "Agent created ",1);
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

const Event* Agent::GetEvent() const
{
	return m_deque->Pop();
}

void Agent::Send(const Event* _event) const
{
	m_hub->Recieve(_event);
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

const string& Agent::GetData(const string& _key) const
{
	map<string, string>::const_iterator dit = m_config.find(_key);
	if(dit != m_config.end())
	{	
		return (*dit).second;
	}
	else
	{			
		throw ("no such field");
	}
}

void Agent::AddAction(const string& _action) 
{ 
	Zlog* z = ZlogGet("mod1");	

	vector<string>::iterator it = find(m_configTokens.begin(), m_configTokens.end(), _action);
	
	if(it == m_configTokens.end())
		return;

	++it;
	do
	{
		m_triggersAndActions[*it] = _action;
		++it;
	} while(it != m_configTokens.end() && *it++ == "|");
	ZLOG_SEND(z, LOG_TRACE, "Action added to agent ",1);
}

void Agent::SetConfig(const string& _key, const string& _val)
{
	m_config[_key] = _val;
}

const string& Agent::GetLocationOfInterest() const
{
	return GetData("From");
}

string Agent::GetNextTriggerIvent() 
{
	if(!m_itSet) 
	{
		m_it = m_triggersAndActions.begin();
		m_itSet = true;
	}

	if(m_it != m_triggersAndActions.end())
	{
		string s = (m_it)->first;
		++(m_it);
		return s;
	}
	else
	{
		return "NO_MORE_TRIGGER_EVENTS";
	}
}

string Agent::GetAction(const string& _event) const 
{
	Zlog* z = ZlogGet("mod1");		
	map<string, string>::const_iterator it = m_triggersAndActions.find(_event);	
	if(it != m_triggersAndActions.end())
	{
		return it->second;
	}
	else if((it = m_triggersAndActions.find("All")) != m_triggersAndActions.end())
	{
		return it->second;
	}
	else
	{
		ZLOG_SEND(z, LOG_TRACE, "No action found ",1);
		return "noaction";
	}
}

void Agent::Run()
{
	if(m_isController)		
	{
		SubscribeToHub();
		m_recievingThread = thread([this] { ProcessEvents(); } );
	}

	m_sendingThread = thread([this] { GenerateEvent(); } );	
}

const string& Agent::GetLog() 
{
	return m_config["log"];
}

void Agent::JoinThreads()
{
	m_recievingThread.join();
	m_sendingThread.join();
}

bool Agent::IsAlive() 
{ 
	return m_isAlive; 
};

void Agent::Stop() 
{ 
	m_isAlive = false; 
}; 































