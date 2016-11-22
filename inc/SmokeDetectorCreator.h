#ifndef __SMOKEDETECTORCREATOR_H__
#define __SMOKEDETECTORCREATOR_H__

#include "AgentCreator.h"

class Config;

class AgentCreator;
class SmokeDetector;

class SmokeDetectorCreator : public AgentCreator
{
public:
	SmokeDetectorCreator();
	virtual ~SmokeDetectorCreator();
	virtual Agent* Create(const Config& _conf, const PubSubHub* _hub) const;

private:
	void operator=(const SmokeDetectorCreator& _crtr);
	SmokeDetectorCreator(const SmokeDetectorCreator& _crtr);
};

extern "C"
void* GetSmokeDetectorCreator();

#endif
