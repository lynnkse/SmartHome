#include <time.h>  
#include <stdlib.h> 
#include <thread>
#include <iostream>
#include <sstream> 
#include <unistd.h>
#include "../inc/Agent.h"
#include "../inc/ElevatorAgent.h"	
#include "../inc/Event.h"

using namespace std;

const int INIT_FLOOR = 5;

ElevatorAgent::ElevatorAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub, true), m_currFloor(INIT_FLOOR) 
{
	AddAction("Go_Down");
}

ElevatorAgent::~ElevatorAgent() {}

void ElevatorAgent::ProcessEvents() 
{
	while(IsAlive()) 
	{	
		Event* e = (Event*) GetEvent();
	
		if(GetAction(e->GetType()) == "Go_Down")  
		{
			time_t timer;
			time(&timer);
			Event* elevatorDownEvent = new Event(timer, GetData("Event"), "Elevator goes down on event of fire\n", GetLocation(), GetLog());
			SendEventToHub(elevatorDownEvent);
		}
		
		delete e;
	}
}

void ElevatorAgent::GenerateEvent() 
{
	while(IsAlive())
	{	
		sleep(1);
		m_currFloor = m_currFloor + (rand()%4 - 2);
		time_t timer;
		time(&timer);
		stringstream buffer;
		buffer << "Elevator moved to " << m_currFloor << "floor" << endl;
		Event* elevatorCurrFloorChange = new Event(timer, GetData("Event"), buffer.str(), GetLocation(), GetLog());
		SendEventToHub(elevatorCurrFloorChange);
	}
}

string ElevatorAgent::GetLocation() const
{
	stringstream buffer;
	buffer << m_currFloor << endl;
	return buffer.str();
}


























































