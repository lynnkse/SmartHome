#include "../inc/LiveLog.h"
#include "../inc/TempSensorAgent.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"
#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include <unistd.h>
#include <iostream>
#include <sstream> 

using namespace std;

TempSensorAgent::TempSensorAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, false)
{}

TempSensorAgent::~TempSensorAgent() 
{}

void LiveLog::ProcessEvents() {}

void LiveLog::GenerateEvent()
{
	while(IsAlive)
	{
		sleep(atoi(GetData("period").c_str()));
		stringstream buffer;
		time_t timer;
		time(&timer);
		int temp = rand() % (atoi(GetData("upper").c_str()) - atoi(GetData("lower").c_str())) + atoi(GetData("lower").c_str());
		buffer << "Temperature: " << temp << endl;
		Event* e = new Event(timer, GetData("Event"), buffer.str(), GetLocation(), GetLog());
		SendEventToHub(e);
	}
}

