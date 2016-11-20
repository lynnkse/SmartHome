#ifndef __AGENT_H__
#define __AGENT_H__

#include <thread>
#include <string>
#include <map>

using namespace std;

class PubSubHub;
class Config;
class Deque;
class Config;
class Event;
template <class T>
class SafeDeque;

class Agent
{
	friend class PubSubHub;

public:
	Agent(const Config& _config, const PubSubHub* _hub);
	virtual ~Agent();
	void SubscribeToHub();
	virtual void Run() = 0;
	
protected:
	const Event* GetEvent();
	const PubSubHub* GetHub() const;
	virtual string GetLocation() const;
	void SendEventToHub(const Event* _event);
	const string& GetData(const string& _key);
	virtual void ProcessEvents() = 0;
	virtual void GenerateEvent() = 0;

private:
	const Agent& operator=(const Agent& _agnt);
	Agent(const Agent& _agnt);
	void Send(const Event* _event) const;
	void Recieve(const Event* _event);
	
	SafeDeque<Event*>* m_deque;
	//string m_id; TODO add this to conf.
	//string m_type;
	//string m_room;
	//string m_floor;
    //string m_log;
	map<string, string> m_config;
	PubSubHub* m_hub;
};

#endif


