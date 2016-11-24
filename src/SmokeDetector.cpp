#include "../inc/SmokeDetector.h"
#include "../inc/Event.h"
#include <unistd.h>
#include <csignal>
#include <iostream>//for test

using namespace std;

SmokeDetector* SmokeDetector::m_detector = 0;

void signalHandler(int signum) 
{	
	SmokeDetector::CreateFireEvent(); 
}

SmokeDetector::SmokeDetector(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, false) 
{}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::ProcessEvents()
{}

void SmokeDetector::GenerateEvent()
{ 	
	if(!m_detector)
	{
		signal(SIGUSR2, signalHandler);
		m_detector = this;
	}
	/*while(1)
	{
		sleep(2);
		time_t timer;
		time(&timer);
		Event* event = new Event(timer, GetData("Event"), "Fire detected", GetLocation(), GetData("log"));

		SendEventToHub(event);
	}*/
}

void SmokeDetector::CreateFireEvent() 
{
	time_t timer;
	time(&timer);
	Event* event = new Event(timer, m_detector->GetData("Event"), "Fire detected", m_detector->GetLocation(), m_detector->GetData("log"));
	m_detector->SendEventToHub(event);
}
