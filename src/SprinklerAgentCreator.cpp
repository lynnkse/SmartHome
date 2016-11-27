#include "../inc/SprinklerAgentCreator.h"
#include "../inc/SprinklerControllerAgent.h"
#include "../inc/Config.h"

SprinklerAgentCreator::SprinklerAgentCreator(){};

SprinklerAgentCreator::~SprinklerAgentCreator(){};

Agent* SprinklerAgentCreator::Create(const Config& _conf, const PubSubHub* _hub) const
{
	return new SprinklerControllerAgent(_conf, _hub);
}

extern "C"
void* GetAgentCreator()
{
	return new SprinklerAgentCreator();
}
