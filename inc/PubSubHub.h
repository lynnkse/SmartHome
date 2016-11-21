#include <vector>
#include <thread>
#include <vector>
#include <map>

using namespace std;

class Agent;
class Event;
template <class T>
class SafeDeque;

class PubSubHub
{
private:
	class Subscribers
	{
	public:
		void InsertAgent(Agent* _agent);
		const vector<Agent*>& GetRelevantAgents(const Event* _event);
		const vector<Agent*>& GetIntersection(vector<vector<Agent*> > &sets);
	private:
		//vector<Agent*> m_agents;
		map<string, vector<Agent*> > m_byEvent;
		map<string, vector<Agent*> > m_byLocation;
		//map<string, vector<Agent*> > m_byEvent;
		vector<Agent*> m_relevantAgents;
	};

public:
	PubSubHub();
	~PubSubHub();	
	void Subscribe(Agent* _agent);
	void Recieve(const Event* _event);
	void Run();
	void ProcessEvents();

private:
	const PubSubHub& operator=(const PubSubHub& _hub);
	PubSubHub(const PubSubHub& _hub);
	void Publish(const Event* _event);
	
	SafeDeque<Event*>* m_events;
	Subscribers m_subs;
	thread m_thread;
};





































