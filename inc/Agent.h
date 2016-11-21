#ifndef __AGENT_H__
#define __AGENT_H__

#include <thread>
#include <string>
#include <map>
#include <vector>

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
	const string& GetData(const string& _key) const;
	virtual void ProcessEvents() = 0;
	virtual void GenerateEvent() = 0;
	void AddAction(const string& _action);
	const string& GetLocationOfInterest() const;
	string GetNextTriggerIvent() const;

private:
	const Agent& operator=(const Agent& _agnt);
	Agent(const Agent& _agnt);
	void Send(const Event* _event) const;
	void Recieve(const Event* _event);
	void SetConfig(const string& _key, const string& _val);
	
	SafeDeque<Event*>* m_deque;
	//set<string> m_actions;
	map<string, string> m_triggersAndActions;
	map<string, string> m_config;
	vector<string> m_configTokens;
	PubSubHub* m_hub;
};

#endif


