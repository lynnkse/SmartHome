#include "../inc/PubSubHub.h"
#include "../inc/Event.h"
#include "../inc/SafeDeque.h"
#include "../inc/Agent.h"

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


void PubSubHub::Subscribe(const Agent* _agent)
{
	m_subs.InsertAgent(_agent);
}

void PubSubHub::Recieve(const Event* _event)
{
	m_events->Push((Event*)_event); //TODO this const??
}

void PubSubHub::Run()
{
	m_thread = thread([this] { ProcessEvents(); } );
}

void PubSubHub::ProcessEvents()
{
	while(1) //FIXME this shoul die
	{	
		Event* event = m_events->Pop();
		Publish(event);
	}
}

























