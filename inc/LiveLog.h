#ifndef __LIVELOG_H__
#define __LIVELOG_H__

#include <map>
#include <map>
#include "../inc/Agent.h"
#include "../inc/TCPServer.h"
#include <vector>
#include <thread>

using namespace std;

class Server;
class LogConfig;
class Config;
class PubSubHub;
class Event;

class LiveLog : public Agent
{
public:
	LiveLog(const Config& _config, const PubSubHub* _hub, const LogConfig& _logConfig);
	~LiveLog();		
	void AddConnection(const string& _userName, const string& _level);
	//virtual void Run();

protected:
	virtual void ProcessEvents();
	virtual void GenerateEvent();

private:
	void operator=(const LiveLog& _log);
	LiveLog(const LiveLog& _log);
		
	map<string, vector<string> > m_connections;
	Server* m_server;
	//SafeDeque* m_eventsQueue;
	//SafeDeque<>* m_newConnections;
	//thread m_recievingThread;
	//thread m_sendingThread;
};

#endif






































