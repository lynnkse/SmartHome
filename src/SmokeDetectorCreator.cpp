#include "../inc/SmokeDetectorCreator.h"
#include "../inc/SmokeDetector.h"
#include "../inc/Config.h"

SmokeDetectorCreator::SmokeDetectorCreator(){};

SmokeDetectorCreator::~SmokeDetectorCreator(){};

Agent* SmokeDetectorCreator::Create(const Config& _conf, const PubSubHub* _hub) const
{
	return new SmokeDetector(_conf, _hub);
}

extern "C"
void* GetAgentCreator()
{
	return new SmokeDetectorCreator();
}
