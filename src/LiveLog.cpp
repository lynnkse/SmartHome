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
	while(IsAlive()) 
	{	
		Event* e = (Event*) GetEvent();
	
		if(GetAction(e->GetType()) == "sendtoserver" && (GetLog() == e->GetLog() || GetLog() == "All"))
		{
			SendEventToServer(e);
		}

		delete e;
	}
}

void LiveLog::GenerateEvent(){}
	
void LiveLog::AddConnection(const string& _userName, const string& _level){}

void LiveLog::SendEventToServer(Event* _event)
{
			string s = "Event: ";
			s += _event->GetData();
			m_server->SendMessage(s);
			s = "Location: ";
			s += _event->GetLocation();
			m_server->SendMessage(s);
			s = "Time: ";
			s += _event->GetTime();
			m_server->SendMessage(s);
			m_server->SendMessage("\n");
}






































































































