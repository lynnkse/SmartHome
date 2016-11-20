#include "../inc/Configurator.h"
#include <string>
#include <vector>
#include "../inc/Config.h"
#include "../inc/LogConfig.h"

Configurator::Configurator(const string& _agentsConfFile, const string& _logConfFile) : m_agentsConfFile("../agents.config"), m_logConfFile("../log.config") {}

Configurator::~Configurator(){};

vector<Config> Configurator::GetAgentsConfigs() const
{
	//TODO fixthis

	vector<Config> vec;
	
	Config conf;
	conf.SetData("type", "ElevatorAgent");
	conf.SetData("id", "elev-1");
	conf.SetData("log", "elevator_log");
	conf.SetData("event", "floor");
	vec.push_back(conf);

	Config conf1;
	conf1.SetData("type", "LiveLog");
	conf1.SetData("id", "live-log");
	vec.push_back(conf1);
	//conf1.SetData("log", "live_log");
	//conf1.SetData("event", "eloor");

	return vec;
}

LogConfig Configurator::GetLogConfig() const
{
	LogConfig conf;
	conf.SetData("port", "8888");
	conf.SetData("ip", "127.0.0.1");
	return conf;
}
