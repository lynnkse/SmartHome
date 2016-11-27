#include "../inc/LiveLog.h"
#include "../inc/TCPServer.h"
#include "../inc/LogConfig.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"
#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include <iostream>

using namespace std;

LiveLog::LiveLog(const Config& _config, const PubSubHub* _hub, const LogConfig& _logConfig) : Agent(_config, _hub, true)
{
	AddAction("sendtoserver");
	m_server = new Server("127.0.0.1", 8888);
	m_server->Run();
}

LiveLog::~LiveLog() 
{
	if(m_server)
	{
		delete m_server;
		m_server = 0;
	}
}

void LiveLog::ProcessEvents()
{
	while(1) //TODO fix this, it should die
	{	
		Event* e = (Event*) GetEvent();
	
		//cout << "Livelog received event. Log: " << e->GetLog() << endl;
	
		if(GetAction(e->GetType()) == "sendtoserver" && (GetLog() == e->GetLog() || GetLog() == "All"))
		{
			//cout << "========>LiveLog msg:" <<e->GetData()  << "Log: " << e->GetLog() << endl;
			m_server->SendMessage(e->GetData());
		}

		delete e;
	}
}

void LiveLog::GenerateEvent(){}
	
void LiveLog::AddConnection(const string& _userName, const string& _level){}






































































































