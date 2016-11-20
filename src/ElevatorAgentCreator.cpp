#include "../inc/ElevatorAgentCreator.h"
#include "../inc/ElevatorAgent.h"
#include "../inc/Config.h"

ElevatorAgentCreator::ElevatorAgentCreator(){};

ElevatorAgentCreator::~ElevatorAgentCreator(){};

Agent* ElevatorAgentCreator::Create(const Config& _conf, const PubSubHub* _hub) const
{
	return new ElevatorAgent(_conf, _hub);
}

extern "C"
AgentCreator* GetElevatorAgentCreator()
{
	return new ElevatorAgentCreator();
}
