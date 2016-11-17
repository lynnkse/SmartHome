#include <map>
#include <map>

class Server;

class LiveLog
{
public:
	LiveLog();
	~LiveLog();	
	void ProcessEvent(const Event& _event) const;	
	void AddConnection(const string& _userName, const string& _level);

private:
	void operator=(const LiveLog& _log);
	void LiveLog(const LiveLog& _log);
	Run();
	
	map<string, vector<string> > m_connections;
	Server* m_server;
	SafeQueue* m_eventsQueue;
	SafeQueue* m_newConnections;
	pthread_t m_eventsThread;
	pthread_t m_connectionsThread;
};
