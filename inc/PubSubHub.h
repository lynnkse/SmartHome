#include <vector>
#include <thread>

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
		void InsertAgent(const Agent* _agent);
		const vector<Agent*>& GetRelevantAgents(const Event* _event);
	private:
		vector<Agent*> m_agents;
		vector<Agent*> m_relevantAgents;
	};

public:
	PubSubHub();
	~PubSubHub();	
	void Subscribe(const Agent* _agent);
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
