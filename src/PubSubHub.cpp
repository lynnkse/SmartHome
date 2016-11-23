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
	
	//cout << "Event of type " << _event->GetType() << ", Log: " << _event->GetLog() << " is being sent to " << relevantSubscribers.size() << endl;

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

	cout << "Num. of relevant agents: " << m_relevantAgents.size() << endl;	

    return m_relevantAgents;
}

void PubSubHub::Subscribers::InsertAgent(Agent* _agent)
{ 
	string loc;
	string event;		
		
	try
	{	
		loc = _agent->GetLocationOfInterest();
		//event = _agent->GetData("InEvent");	
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

	event = _agent->GetNextTriggerIvent();
	while(event != "NO_MORE_TRIGGER_EVENTS")
	{	
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
		event = _agent->GetNextTriggerIvent();
	}
}

const vector<Agent*>& PubSubHub::Subscribers::GetRelevantAgents(const Event* _event) 
{ 
	vector<vector<Agent*> > sets;
	vector<Agent*> byLoc;	
	vector<Agent*> byEve;
	bool added = false;
	
	m_relevantAgents.clear();	

	string s = _event->GetType();

	map<string, vector<Agent*> >::const_iterator it_loc = m_byLocation.find(_event->GetLocation());
	if(it_loc != m_byLocation.end())
	{
		byLoc.insert(byLoc.end(), it_loc->second.begin(), it_loc->second.end());	
		//sets.push_back(it_loc->second);	
		added = true;
	}
	
	it_loc = m_byLocation.find("All");
	if(it_loc != m_byLocation.end())
	{
		byLoc.insert(byLoc.end(), it_loc->second.begin(), it_loc->second.end());
		//sets.push_back(it_loc->second);		
		added = true;
	}
	if(!added)
		return m_relevantAgents;

	added = false;	
	
	map<string, vector<Agent*> >::const_iterator it_event = m_byEvent.find(_event->GetType());
	if(it_event != m_byEvent.end())
	{
		byEve.insert(byEve.end(), it_event->second.begin(), it_event->second.end());
		//sets.push_back(it_event->second);			
		added = true;
	}

	it_event = m_byEvent.find("All");
	if(it_event != m_byEvent.end())
	{
		byEve.insert(byEve.end(), it_event->second.begin(), it_event->second.end());	
		//sets.push_back(it_event->second);
		added = true;
		//cout << "Here i am " << it_event->second.size() << endl;
	}
	if(!added)
		return m_relevantAgents;
	
	sets.push_back(byEve);
	sets.push_back(byLoc);

	//cout << byEve.size() << byLoc.size() << endl;

	//cout << "Event log: " << _event->GetType() << endl;

	return GetIntersection(sets);
} 

void PubSubHub::JoinThreads() 
{
	m_thread.join();
}

















