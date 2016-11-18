#include <time.h>  
#include <stdlib.h> 
#include <thread>
#include <iostream>
#include <sstream> 
#include "../inc/Agent.h"
#include "../inc/ElevatorAgent.h"
#include "../inc/Event.h"

using namespace std;

const int INIT_FLOOR = 5;

ElevatorAgent::ElevatorAgent(const Config& _config, const PubSubHub* _hub) : Agent(_config, _hub), m_currFloor(INIT_FLOOR) {}

ElevatorAgent::~ElevatorAgent() {}

void ElevatorAgent::Run()
{
	//m_recievingThread = thread(&ElevatorAgent::ProcessEvents, this);
	m_recievingThread = thread([this] { ProcessEvents(); } );
	m_sendingThread = thread([this] { GenerateEvent(); } );	
	
	/*if(pthread_create(&m_recievingThread, NULL, &ProcessEvents, NULL))
	{
		throw ("couldn't start thread'");
	}
	
	if(pthread_create(&m_sendingThread, NULL, , NULL))
	{
		throw ("couldn't start thread'");
	}*/
}

void ElevatorAgent::ProcessEvents() 
{
	while(1) //TODO fix this, it should die
	{	
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
		m_currFloor = m_currFloor + (rand()%4 - 2);
		time_t timer;
		time(&timer);
		stringstream buffer;
		buffer << "Elevator moved to " << m_currFloor << "floor" << endl;
		Event* elevatorCurrFloorChange = new Event(timer, "Elevator_Action", buffer.str(), GetLocation());
		SendEventToHub(elevatorCurrFloorChange);
	}
}

string ElevatorAgent::GetLocation() const
{
	stringstream buffer;
	buffer << m_currFloor << endl;
	return buffer.str();
}


























































