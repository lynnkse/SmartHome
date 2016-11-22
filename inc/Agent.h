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
	Agent(const Config& _config, const PubSubHub* _hub, bool _isController);
	virtual ~Agent();
	void SubscribeToHub();
	virtual void Run();
	
protected:
	const Event* GetEvent();
	const PubSubHub* GetHub() const;
	virtual string GetLocation() const;
	void SendEventToHub(const Event* _event);
	const string& GetData(const string& _key) const;
	virtual void ProcessEvents() = 0;
	virtual void GenerateEvent() = 0;
	void AddAction(const string& _action);
	string GetAction(const string& _event) const;
	const string& GetLocationOfInterest() const;
	string GetNextTriggerIvent();

private:
	const Agent& operator=(const Agent& _agnt);
	Agent(const Agent& _agnt);
	void Send(const Event* _event) const;
	void Recieve(const Event* _event);
	void SetConfig(const string& _key, const string& _val);
	
	SafeDeque<Event*>* m_deque;
	bool m_isController;
	map<string, string> m_triggersAndActions;
	map<string, string> m_config;
	vector<string> m_configTokens;
	PubSubHub* m_hub;
	map<string, string>::iterator m_it;
	bool m_itSet;
	thread m_recievingThread;
	thread m_sendingThread;
};

#endif


