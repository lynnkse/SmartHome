#include "../inc/LiveLog.h"
//#include "../inc/Server.h"
#include "../inc/LogConfig.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"
#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include <iostream>

using namespace std;

LiveLog::LiveLog(const Config& _config, const PubSubHub* _hub, const LogConfig& _logConfig) : Agent(_config, _hub)
{
	//TODO set server here
	//cout << "LiveLog: LiveLog Created" << endl;
}

LiveLog::~LiveLog() {}

void LiveLog::Run()
{
	SubscribeToHub();	
	m_recievingThread = thread([this] { ProcessEvents(); } );
	m_sendingThread = thread([this] { GenerateEvent(); } );	
}	

void LiveLog::ProcessEvents()
{
	//cout << "LiveLog ProcessEvents" << endl;	
	while(1) //TODO fix this, it should die
	{	
		Event* e = (Event*) GetEvent();
	
		cout << "========>LiveLog msg:" <<e->GetData() << endl;

		delete e;
	}
}

void LiveLog::GenerateEvent(){}
	
void LiveLog::AddConnection(const string& _userName, const string& _level){}






































































































