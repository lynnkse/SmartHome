#include "../inc/Configurator.h"
#include "../inc/Config.h"
#include <vector>
#include "../inc/AgentFactory.h"
#include "../inc/AgentLifecycleManager.h"
#include "../inc/PubSubHub.h"
#include <unistd.h>
#include <dlfcn.h>
#include <set>
#include "../inc/logmngr.h"
#include <iostream>

using namespace std;

typedef void* (*F)();

void LoadAndAddCreator(const Config& _config, AgentFactory& _factory)
{
	static set<string> loadedCreators;

	string s = "./";
	s += _config.GetData("type");
	s += ".so";

	if(loadedCreators.find(s) == loadedCreators.end())
	{
		void* handle = dlopen(s.c_str(), RTLD_LAZY); 
		if (!handle) 
    	{ 
			fprintf(stderr, "dlopen failed: %s\n", dlerror()); 
      		exit(EXIT_FAILURE); 
		};
		F func = (F) dlsym(handle, "GetAgentCreator");
		AgentCreator* creator = (AgentCreator*) func();
		_factory.AddCreator(_config.GetData("type"), creator);
		loadedCreators.insert(s);
	}
}

int main()
{
	ZlogInit("log.config");
	Zlog* z = ZlogGet("mod1");

	Configurator configurator("agents.config");
	vector<Config> configs = configurator.GetAgentsConfigs();

	AgentFactory& agentFactory = AgentFactory::GetInstance();

	for(vector<Config>::const_iterator it = configs.begin(); it != configs.end(); ++it)
	{
		LoadAndAddCreator(*it, agentFactory);
		ZLOG_SEND(z, LOG_TRACE, "agent creator added to factory ",1);
	}

	PubSubHub hub;
	hub.Run();

	AgentLifecycleManager lifecycleManager(&agentFactory, &hub);

	lifecycleManager.CreateAgents(configs);

	lifecycleManager.DestroyAgents();
	hub.JoinThreads();
	
	LogManagerDestroy();

	return 0;
}







































