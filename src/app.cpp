#include "../inc/Configurator.h"
#include "../inc/Config.h"
#include <vector>
#include "../inc/AgentFactory.h"
#include "../inc/AgentLifecycleManager.h"
#include "../inc/PubSubHub.h"
#include "../inc/ElevatorAgentCreator.h"
#include "../inc/SmokeDetectorCreator.h"
#include "../inc/LiveLogCreator.h"
#include <unistd.h>
#include <dlfcn.h>

using namespace std;

typedef void* (*F)();

void LoadAndAddCreator(const Config& _config, AgentFactory& _factory)
{
	/*string s = _"../";
	s += config.GetData("type");
	s += ".so";
	dlopen(s, RTLD_NOW); TODO make sure it isn't open twice*/

	string s = _config.GetData("type");

	if(s == "ElevatorAgent") 
	{	
		void* handle = dlopen("./ElevatorAgent.so", RTLD_LAZY); //TODO make sure it isn't open twice
		F func = (F) dlsym(handle, "GetElevatorAgentCreator");
		AgentCreator* creator = (AgentCreator*) func();
		_factory.AddCreator("ElevatorAgent", creator);
	}	
	else if(s == "LiveLog")
	{	
		void* handle = dlopen("./LiveLog.so", RTLD_LAZY);
		F func = (F) dlsym(handle, "GetLiveLogCreator");
		AgentCreator* creator = (AgentCreator*) func(); 
		_factory.AddCreator("LiveLog", creator);
	}
	else if(s == "SmokeDetector")
	{	
		void* handle = dlopen("./SmokeDetector.so", RTLD_LAZY);
		F func = (F) dlsym(handle, "GetSmokeDetectorCreator");
		AgentCreator* creator = (AgentCreator*) func(); 
		_factory.AddCreator("SmokeDetector", creator);
	}
}

int main()
{
	Configurator configurator("agents.config", "who cares");
	vector<Config> configs = configurator.GetAgentsConfigs();

	AgentFactory& agentFactory = AgentFactory::GetInstance();
	//ElevatorAgentCreator creator; 
	//agentFactory.AddCreator("ElevatorAgent", &creator);
	//LiveLogCreator creator1; 
	//agentFactory.AddCreator("LiveLog", &creator1);	

	for(vector<Config>::const_iterator it = configs.begin(); it != configs.end(); ++it)
	{
		LoadAndAddCreator(*it, agentFactory);
	}

	PubSubHub hub;
	hub.Run();

	AgentLifecycleManager lifecycleManager(&agentFactory, &hub);

	lifecycleManager.CreateAgents(configs);

	lifecycleManager.DestroyAgents();
	hub.JoinThreads();

	//sleep(999999);

	return 0;
}
