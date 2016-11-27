#include "../inc/SmokeDetector.h"
#include "../inc/Event.h"
#include <unistd.h>
#include <csignal>

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
}


void SmokeDetector::CreateFireEvent() 
{
	m_detector->SendEventToHub(new Event(time(0), m_detector->GetData("Event"), "Fire_Detected", m_detector->GetLocation(), m_detector->GetData("log")));
}
