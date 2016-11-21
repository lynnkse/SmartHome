#include "../inc/PubSubHub.h"
#include "../inc/Event.h"
#include "../inc/SafeDeque.h"
#include "../inc/Agent.h"
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include <iostream>//for test
using namespace std;

PubSubHub::PubSubHub()
{
	m_events = new SafeDeque<Event*>();
}

PubSubHub::~PubSubHub()
{
	if(m_events)
	{
		delete m_events;
		m_events = 0;
	}
}

void PubSubHub::Publish(const Event* _event) 
{
	const vector<Agent*>& relevantSubscribers = m_subs.GetRelevantAgents(_event);
	for(vector<Agent*>::const_iterator it = relevantSubscribers.begin(); it != relevantSubscribers.end(); ++it)
	{
		(*it)->Recieve(new Event(*_event));	
	} 
	delete _event;
}


void PubSubHub::Subscribe(Agent* _agent)
{
	m_subs.InsertAgent(_agent);
	//cout << "Agent inserted" << endl;
}

void PubSubHub::Recieve(const Event* _event)
{
	m_events->Push((Event*)_event); //TODO this const??
}

void PubSubHub::Run()
{
	m_thread = thread([this] { ProcessEvents(); } );
	
	//cout << "Hub run" << endl;
}

void PubSubHub::ProcessEvents()
{
	while(1) //FIXME this shoul die
	{	
		Event* event = m_events->Pop();
		Publish(event);
	}
}

const vector<Agent*>& PubSubHub::Subscribers::GetIntersection(vector<vector<Agent*> > &sets)
{   
	for (vector<Agent*>::iterator it = sets[0].begin(); it != sets[0].end(); ++it)
    {
        Agent* elem = *it;
 
        bool bFound = true;
 
        for (int j = 1; j < sets.size() ; j++)
        {
            if (find(sets[j].begin(), sets[j].end(), elem) == sets[j].end())
            {
               bFound = false;
            }
        }
 
        if (bFound)
        {
                m_relevantAgents.push_back(elem);
        }
    }
    return m_relevantAgents;
}

void PubSubHub::Subscribers::InsertAgent(Agent* _agent)
{ 
	string loc;
	string event;		
		
	try
	{	
		loc = _agent->GetData("From");
		event = _agent->GetData("InEvent");	
	}
	catch(const char* _e)
	{
		cout << _e << endl;
		return;
	}
	
	map<string, vector<Agent*> >::iterator it = m_byLocation.find(loc);
	if(m_byLocation.find(loc) != m_byLocation.end())	
	{
		(it->second).push_back(_agent);
	}
	else
	{
		vector<Agent*> vec;
		vec.push_back(_agent);
		m_byLocation[loc] = vec;
	}

	it = m_byEvent.find(event);
	if(m_byEvent.find(event) != m_byEvent.end())	
	{
		it->second.push_back(_agent);
	}
	else
	{
		vector<Agent*> vec;
		vec.push_back(_agent);
		m_byEvent[event] = vec;
	}
}

const vector<Agent*>& PubSubHub::Subscribers::GetRelevantAgents(const Event* _event) 
{ 
	m_relevantAgents.clear();	

	map<string, vector<Agent*> >::const_iterator it_loc = m_byLocation.find(_event->GetLocation());
	if(it_loc == m_byLocation.end())
	{
		it_loc = m_byLocation.find("All");
	}
	if(it_loc == m_byLocation.end())
		return m_relevantAgents;	
	
	map<string, vector<Agent*> >::const_iterator it_event = m_byEvent.find(_event->GetType());
	if(it_event == m_byEvent.end())
	{
		it_event = m_byEvent.find("All");
	}
	if(it_event == m_byEvent.end())
		return m_relevantAgents;

	vector<vector<Agent*> > sets;
	sets.push_back(it_loc->second);
	sets.push_back(it_event->second);
	return GetIntersection(sets);
} 



















