#include <time.h>  
#include <stdlib.h> 
#include <thread>
#include <iostream>
#include <sstream> 
#include <unistd.h>
#include "../inc/Agent.h"
#include "../inc/HVACcontrollerAgent.h"	
#include "../inc/Event.h"

using namespace std;

HVACcontrollerAgent::HVACcontrollerAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, true)
{
	AddAction("shutdown");
}

HVACcontrollerAgent::~HVACcontrollerAgent() {}

void HVACcontrollerAgent::ProcessEvents() 
{
	while(IsAlive()) 
	{	
		Event* e = (Event*) GetEvent();
	
		if(GetAction(e->GetType()) == "shutdown")  
		{
			time_t timer;
			time(&timer);
			Event* e = new Event(timer, GetData("Event"), "HVAC shutdown\n", GetLocation(), GetLog());
			SendEventToHub(e);
		}
		
		delete e;
	}
}

void HVACcontrollerAgent::GenerateEvent() 
{}


