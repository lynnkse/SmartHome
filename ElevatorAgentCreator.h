class AgentCreator;
class FireSensorAgent;

class ElevatorAgentCreator : public AgentCreator
{
public:
	ElevatorAgentCreator(){};
	virtual ~ElevatorAgentCreator(){};
	FireSensorAgent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const ElevatorAgentCreator& _crtr);
	ElevatorAgentCreator(const ElevatorAgentCreator& _crtr);
};
