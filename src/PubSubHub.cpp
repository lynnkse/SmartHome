#include "../inc/PubSubHub.h"
#include "../inc/Event.h"
#include "../inc/SafeDeque.h"
#include "../inc/Agent.h"
#include <vector>
#include <algorithm>
#include <map>

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


void PubSubHub::Subscribe(const Agent* _agent)
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
		//cout << "Hub ProcessEvents" << endl;
		Event* event = m_events->Pop();
		Publish(event);
	}
}

vector<int> PubSubHub::GetIntersection(vector<vector<int> > &sets)
{
    vector<int> result;  
    int smallSetInd = 0;  
    int minSize = sets[0].size(); 
 
    // sort all the sets, and also find the smallest set
    for (int i = 1 ; i < sets.size() ; i++)
    {
        // sort this set
        sort(sets[i].begin(), sets[i].end());
 
        // update minSize, if needed
        if (minSize > sets[i].size())
        {
            minSize = sets[i].size();
            smallSetInd = i;
        }
    }
 
    map<int,int> elementsMap;
 
    // Add all the elements of smallest set to a map, if already present,
    // update the frequency
    for (int i = 0; i < sets[smallSetInd].size(); i++)
    {
        if (elementsMap.find( sets[smallSetInd][i] ) == elementsMap.end())
            elementsMap[ sets[smallSetInd][i] ] = 1;
        else
            elementsMap[ sets[smallSetInd][i] ]++;
    }
 
    // iterate through the map elements to see if they are present in
    // remaining sets
    map<int,int>::iterator it;
    for (it = elementsMap.begin(); it != elementsMap.end(); ++it)
    {
        int elem = it->first;
        int freq = it->second;
 
        bool bFound = true;
 
        // Iterate through all sets
        for (int j = 0 ; j < sets.size() ; j++)
        {
            // If this set is not the smallest set, then do binary search in it
            if (j != smallSetInd)
            {
                // If the element is found in this set, then find its frequency
                if (binary_search( sets[j].begin(), sets[j].end(), elem ))
                {
                   int lInd = lower_bound(sets[j].begin(), sets[j].end(), elem)
                                                            - sets[j].begin();
                   int rInd = upper_bound(sets[j].begin(), sets[j].end(), elem)
                                                            - sets[j].begin();
 
                   // Update the minimum frequency, if needed
                   if ((rInd - lInd) < freq)
                       freq = rInd - lInd;
                }
                // If the element is not present in any set, then no need 
                // to proceed for this element.
                else
                {
                    bFound = false;
                    break;
                }
            }
        }
 
        // If element was found in all sets, then add it to result 'freq' times
        if (bFound)
        {
            for (int k = 0; k < freq; k++)
                result.push_back(elem);
        }
    }
    return result;
}























