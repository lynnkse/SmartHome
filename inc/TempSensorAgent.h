class Agent;
class PubSubHub;
class Config;
class Event;

#include "../inc/Agent.h"

class TempSensorAgent : public Agent
{
public:
	TempSensorAgent(const Config& _config, const PubSubHub* _hub);
	~TempSensorAgent();
	void ProcessEvents();
	void GenerateEvent();
	
protected:

private:
	void operator=(const Agent& _agnt);
	TempSensorAgent(const Agent& _agnt);

	int upper;
	int lower;
	int period;
};
