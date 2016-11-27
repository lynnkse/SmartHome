#include "../inc/HVACagentCreator.h"
#include "../inc/HVACcontrollerAgent.h"
#include "../inc/Config.h"

HVACagentCreator::HVACagentCreator(){};

HVACagentCreator::~HVACagentCreator(){};

Agent* HVACagentCreator::Create(const Config& _conf, const PubSubHub* _hub) const
{
	return new HVACcontrollerAgent(_conf, _hub);
}

extern "C"
void* GetAgentCreator()
{
	return new HVACagentCreator();
}
