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

/*void ElevatorAgent::Run()
{
	SubscribeToHub();	
	m_recievingThread = thread([this] { ProcessEvents(); } );
	m_sendingThread = thread([this] { GenerateEvent(); } );	
	//cout << "Elevator run" << endl;
}*/

void ElevatorAgent::ProcessEvents() 
{
	while(IsAlive()) //TODO fix this, it should die
	{	
		//cout << "Elevator ProcessEvents" << endl;	
	
		Event* e = (Event*) GetEvent();
	
		if(e->GetType() == "Fire_Detected")
		{
			time_t timer;
			time(&timer);
			//cout << "Evelator recived event. Log: " << e->GetLog() << endl;
			Event* elevatorDownEvent = new Event(timer, GetData("Event"), "Elevator goes down on event of fire", GetLocation(), GetLog());
			SendEventToHub(elevatorDownEvent);
		}
		
		delete e;
	}
	//cout << "End of ElevatorAgent::ProcessEvents()" << endl;
}

void ElevatorAgent::GenerateEvent() 
{
	while(IsAlive())
	{
		//cout << "Elevator GenerateEvent" << endl;			
		sleep(1);
		m_currFloor = m_currFloor + (rand()%4 - 2);
		time_t timer;
		time(&timer);
		stringstream buffer;
		buffer << "Elevator moved to " << m_currFloor << "floor" << endl;
		Event* elevatorCurrFloorChange = new Event(timer, GetData("Event"), buffer.str(), GetLocation(), GetLog());
		SendEventToHub(elevatorCurrFloorChange);
	}
	//cout << "End of ElevatorAgent::GenerateEvent()" << endl;
}

string ElevatorAgent::GetLocation() const
{
	stringstream buffer;
	buffer << m_currFloor << endl;
	return buffer.str();
}


























































