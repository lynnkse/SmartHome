class AgentCreator;
class SprinklerControllerAgent;

class SprinklerAgentCreator : public AgentCreator
{
public:
	SprinklerAgentCreator(){};
	virtual ~SprinklerAgentCreator(){};
	SprinklerControllerAgent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const SprinklerAgentCreator& _crtr);
	SprinklerAgentCreator(const SprinklerAgentCreator& _crtr);
};
