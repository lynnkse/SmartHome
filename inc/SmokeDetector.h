#ifndef __SMOKEDETECTOR_H__
#define __SMOKEDETECTOR_H__

#include "../inc/Agent.h"

class PubSubHub;
class Config;

class SmokeDetector : public Agent
{
public:
	SmokeDetector(const Config& _config, const PubSubHub* _hub);
	~SmokeDetector();

	//static void CreateFireEvent();//to handle event

protected:
	virtual void ProcessEvents();
	virtual void GenerateEvent();

private:
	void operator=(const Agent& _agnt);
	SmokeDetector(const Agent& _agnt);
	
	//static SmokeDetector* m_detector;
};

#endif
