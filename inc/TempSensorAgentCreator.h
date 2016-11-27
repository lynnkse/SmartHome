#ifndef __TEMPSENSORAGENTCREATOR_H__
#define __TEMPSENSORAGENTCREATOR_H__

#include "../inc/AgentCreator.h"
#include "../inc/Agent.h"

class AgentCreator;
class TempSensorAgent;

class TempSensorAgentCreator : public AgentCreator
{
public:
	TempSensorAgentCreator();
	virtual ~TempSensorAgentCreator();
	virtual Agent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const TempSensorAgentCreator& _crtr);
	TempSensorAgentCreator(const TempSensorAgentCreator& _crtr);
};

extern "C"
void* GetAgentCreator();

#endif
