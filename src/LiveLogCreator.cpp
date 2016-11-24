#include "../inc/LiveLogCreator.h"
#include "../inc/LiveLog.h"
#include "../inc/Config.h"
#include "../inc/LogConfig.h"//for testing

LiveLogCreator::LiveLogCreator(){};

LiveLogCreator::~LiveLogCreator(){};

Agent* LiveLogCreator::Create(const Config& _conf, const PubSubHub* _hub) const
{
	LogConfig* logConfig = new LogConfig();
	return new LiveLog(_conf, _hub, *logConfig);
}

extern "C"
void* GetAgentCreator()
{
	return new LiveLogCreator();
}
