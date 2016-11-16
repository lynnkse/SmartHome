class AgentCreator;
class TempSensorAgent;

class TempSensorAgentCreator : public AgentCreator
{
public:
	TempSensorAgentCreator(){};
	virtual ~TempSensorAgentCreator(){};
	TempSensorAgent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const TempSensorAgentCreator& _crtr);
	TempSensorAgentCreator(const TempSensorAgentCreator& _crtr);
};
