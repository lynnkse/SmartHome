#include "../inc/SmokeDetector.h"
#include "../inc/Event.h"
#include <unistd.h>
#include <iostream>//for test

using namespace std;

SmokeDetector::SmokeDetector(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, false) {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::ProcessEvents()
{}

void SmokeDetector::GenerateEvent()
{
	while(1)
	{
		sleep(2);
		time_t timer;
		time(&timer);
		Event* event = new Event(timer, GetData("Event"), "Fire detected", GetLocation(), GetData("log"));
		
		//cout << "=================================> Event created. Log : " << event->GetLog() << endl;

		SendEventToHub(event);
	}
}
