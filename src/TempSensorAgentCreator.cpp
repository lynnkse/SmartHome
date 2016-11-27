#include "../inc/TempSensorAgentCreator.h"
#include "../inc/TempSensorAgent.h"
#include "../inc/Config.h"

TempSensorAgentCreator::TempSensorAgentCreator(){};

TempSensorAgentCreator::~TempSensorAgentCreator(){};

Agent* TempSensorAgentCreator::Create(const Config& _conf, const PubSubHub* _hub) const
{
	return new TempSensorAgent(_conf, _hub);
}

extern "C"
void* GetAgentCreator()
{
	return new TempSensorAgentCreator();
}
