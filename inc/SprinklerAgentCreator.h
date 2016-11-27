#ifndef __SPRINKLERAGENTCREATOR_H__
#define __SPRINKLERAGENTCREATOR_H__

class AgentCreator;
class SprinklerControllerAgent;

#include "../inc/AgentCreator.h"

class SprinklerAgentCreator : public AgentCreator
{
public:
	SprinklerAgentCreator();
	virtual ~SprinklerAgentCreator();
	Agent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const SprinklerAgentCreator& _crtr);
	SprinklerAgentCreator(const SprinklerAgentCreator& _crtr);
};

extern "C"
void* GetAgentCreator();

#endif
