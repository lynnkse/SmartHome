#include "../inc/LiveLog.h"
#include "../inc/TempSensorAgent.h"
#include "../inc/Config.h"
#include "../inc/PubSubHub.h"
#include "../inc/SafeDeque.h"
#include "../inc/Event.h"
#include <unistd.h>
#include <iostream>
#include <sstream> 
#include <vector>
#include <algorithm>

using namespace std;

TempSensorAgent::TempSensorAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, false)
{
	const vector<string>& vec = GetConfig();
	vector<string>::const_iterator it = find(vec.begin(), vec.end(), "upper");
	++it;	
	upper = stoi(*it);
	it = find(vec.begin(), vec.end(), "lower");
	++it;	
	lower = stoi(*it);
	it = find(vec.begin(), vec.end(), "period");
	++it;	
	period = stoi(*it);
}

TempSensorAgent::~TempSensorAgent() 
{}

void TempSensorAgent::ProcessEvents() {}

void TempSensorAgent::GenerateEvent()
{
	while(IsAlive)
	{
		sleep(period);
		stringstream buffer;
		time_t timer;
		time(&timer);
		int temp = rand() % (upper - lower) + lower;
		buffer << "Temperature: " << temp << endl;
		Event* e = new Event(timer, GetData("Event"), buffer.str(), GetLocation(), GetLog());
		SendEventToHub(e);
	}
}

