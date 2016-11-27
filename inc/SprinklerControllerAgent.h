#ifndef __SPRINKLERCONTROLLERAGENT_H__
#define __SPRINKLERCONTROLLERAGENT_H__

class PubSubHub;
class Config;
class Config;
class Event;

#include "../inc/Agent.h"

class SprinklerControllerAgent : public Agent
{
public:
	SprinklerControllerAgent(const Config& _config, const PubSubHub* _hub);
	~SprinklerControllerAgent();
	void ProcessEvents();
	void GenerateEvent();
	
protected:

private:
	void operator=(const Agent& _agnt);
	SprinklerControllerAgent(const Agent& _agnt);
};

#endif
