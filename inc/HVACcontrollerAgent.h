#ifndef __HVACCONTROLLERAGENT_H__
#define __HVACCONTROLLERAGENT_H__

class PubSubHub;
class Config;
class Config;
class Event;

#include "../inc/Agent.h"

class HVACcontrollerAgent : public Agent
{
public:
	HVACcontrollerAgent(const Config& _config, const PubSubHub* _hub);
	~HVACcontrollerAgent();
	void ProcessEvents();
	void GenerateEvent();
	
protected:

private:
	void operator=(const Agent& _agnt);
	HVACcontrollerAgent(const Agent& _agnt);
};

#endif
