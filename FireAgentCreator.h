class AgentCreator;
class FireSensorAgent;

class FireAgentCreator : public AgentCreator
{
public:
	FireAgentCreator(){};
	virtual ~FireAgentCreator(){};
	FireSensorAgent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const FireAgentCreator& _crtr);
	FireAgentCreator(const FireAgentCreator& _crtr);
};
