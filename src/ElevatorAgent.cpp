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

ElevatorAgent::ElevatorAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub), m_currFloor(INIT_FLOOR) 
{
	AddAction("Go_Down");
}

ElevatorAgent::~ElevatorAgent() {}

void ElevatorAgent::Run()
{
	SubscribeToHub();	
	m_recievingThread = thread([this] { ProcessEvents(); } );
	m_sendingThread = thread([this] { GenerateEvent(); } );	
	//cout << "Elevator run" << endl;
}

void ElevatorAgent::ProcessEvents() 
{
	while(1) //TODO fix this, it should die
	{	
		//cout << "Elevator ProcessEvents" << endl;	
	
		Event* e = (Event*) GetEvent();
	
		if(e->GetType() == "Fire_Detected")
		{
			time_t timer;
			time(&timer);
			Event* elevatorDownEvent = new Event(timer, "Elevator_Action", "Elevator goes down on event of fire", GetLocation());
			SendEventToHub(elevatorDownEvent);
		}
		
		delete e;
	}
}

void ElevatorAgent::GenerateEvent() 
{
	while(1)
	{
		//cout << "Elevator GenerateEvent" << endl;			
		sleep(1);
		m_currFloor = m_currFloor + (rand()%4 - 2);
		time_t timer;
		time(&timer);
		stringstream buffer;
		buffer << "Elevator moved to " << m_currFloor << "floor" << endl;
		Event* elevatorCurrFloorChange = new Event(timer, GetData("Event"), buffer.str(), GetLocation());
		SendEventToHub(elevatorCurrFloorChange);
	}
}

string ElevatorAgent::GetLocation() const
{
	stringstream buffer;
	buffer << m_currFloor << endl;
	return buffer.str();
}


























































