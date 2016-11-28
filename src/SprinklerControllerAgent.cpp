#include <time.h>  
#include <stdlib.h> 
#include <thread>
#include <iostream>
#include <sstream> 
#include <unistd.h>
#include "../inc/Agent.h"
#include "../inc/SprinklerControllerAgent.h"	
#include "../inc/Event.h"

using namespace std;

SprinklerControllerAgent::SprinklerControllerAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, true)
{
	AddAction("On");
}

SprinklerControllerAgent::~SprinklerControllerAgent() {}

void SprinklerControllerAgent::ProcessEvents() 
{
	while(IsAlive()) 
	{	
		Event* e = (Event*) GetEvent();
	
		if(GetAction(e->GetType()) == "On")  
		{
			time_t timer;
			time(&timer);
			Event* e = new Event(timer, GetData("Event"), "Sprinkler is on\n", GetLocation(), GetLog());
			SendEventToHub(e);
		}
		
		delete e;
	}
}

void SprinklerControllerAgent::GenerateEvent(){}
