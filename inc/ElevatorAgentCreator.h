#include "AgentCreator.h"

class Config;

class AgentCreator;
class ElevatorAgent;

class ElevatorAgentCreator : public AgentCreator
{
public:
	ElevatorAgentCreator();
	virtual ~ElevatorAgentCreator();
	virtual Agent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const ElevatorAgentCreator& _crtr);
	ElevatorAgentCreator(const ElevatorAgentCreator& _crtr);
};
