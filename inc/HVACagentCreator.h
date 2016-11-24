#ifndef __HVACAGENTCREATOR_H__
#define __HVACAGENTCREATOR_H__

class AgentCreator;
class HVACcontrollerAgent;

class HVACagentCreator : public AgentCreator
{
public:
	HVACagentCreator(){};
	virtual ~HVACagentCreator(){};
	HVACcontrollerAgent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const HVACagentCreator& _crtr);
	HVACagentCreator(const HVACagentCreator& _crtr);
};

extern "C"
void* GetAgentCreator();

#endif
