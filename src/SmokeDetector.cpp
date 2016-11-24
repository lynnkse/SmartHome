#include "../inc/SmokeDetector.h"
#include "../inc/Event.h"
#include <unistd.h>
#include <csignal>
#include <iostream>//for test

using namespace std;

//static SmokeDetector* m_detector = 0;

/*void signalHandler(int signum) 
{
	SmokeDetector::CreateFireEvent(); 
}*/

SmokeDetector::SmokeDetector(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, false) {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::ProcessEvents()
{}

void SmokeDetector::GenerateEvent()
{
//	signal(SIGINT, signalHandler); 	
	while(1)
	{
		sleep(2);
		time_t timer;
		time(&timer);
		Event* event = new Event(timer, GetData("Event"), "Fire detected", GetLocation(), GetData("log"));

		SendEventToHub(event);
	}
}

/*static void SmokeDetector::CreateFireEvent() 
{
	time_t timer;
	time(&timer);
	Event* event = new Event(timer, GetData("Event"), "Fire detected", GetLocation(), GetData("log"));
}*/
