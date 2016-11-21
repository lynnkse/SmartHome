#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include "../inc/Agent.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"
#include <iostream>
#include <algorithm>
#include "../inc/Tokenizer_t.h"

using namespace std;

Agent::Agent(const Config& _config, const PubSubHub* _hub) : m_config(_config.GetConfig())
{
	if(!_hub) 
		{
			cout << "Agent: Agent()" << endl;		
			throw("nullptr exception");	
		}	
	else
		m_hub = (PubSubHub*) _hub;

	Tokenizer_t t;

	m_configTokens = t.GetStringTokens(m_config["config"]); 

	vector<string>::iterator it = find(m_configTokens.begin(), m_configTokens.end(), "From");
	if(it != m_configTokens.end())
	{
		++it;
		SetConfig("From", *it);
	}
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

const string& Agent::GetData(const string& _key) const
{
	map<string, string>::const_iterator it = m_config.find(_key);
	if(it != m_config.end())
	{	
		return (*it).second;
	}
	else
	{		
		cout << "Agent::GetData(); " << _key << endl;		
		throw ("no such field");
	}
}

void Agent::AddAction(const string& _action) 
{ 
	//m_actions.insert(_action);
	
	vector<string>::iterator it = find(m_configTokens.begin(), m_configTokens.end(), _action);
	do
	{
		m_triggersAndActions[*it] = _action;
		++it;
	} while(*it++ == "|");
}

void Agent::SetConfig(const string& _key, const string& _val)
{
	m_config[_key] = _val;
}

const string& Agent::GetLocationOfInterest() const
{
	return GetData("From");
}

string Agent::GetNextTriggerIvent() const
{
	static map<string, string>::const_iterator it = m_triggersAndActions.begin();
	
	if(it != m_triggersAndActions.end())
	{
		string s = it->first;
		++it;
		return s;
	}
	else
	{
		return "NO_MORE_TRIGGER_EVENTS";
	}
}











































