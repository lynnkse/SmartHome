#ifndef __LIVELOGCREATOR_H__
#define __LIVELOGCREATOR_H__

#include "AgentCreator.h"

class Config;

class AgentCreator;
class LiveLog;

class LiveLogCreator : public AgentCreator
{
public:
	LiveLogCreator();
	virtual ~LiveLogCreator();
	virtual Agent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const LiveLogCreator& _crtr);
	LiveLogCreator(const LiveLogCreator& _crtr);
};

extern "C"
AgentCreator* GetLiveLogCreator();

#endif
