#ifndef __CONFIGURATOR_H__
#define __CONFIGURATOR_H__

#include <vector>
#include <string>

using namespace std;

class Config;
class LogConfig;

class Configurator
{
public:
	~Configurator();
	Configurator(const string& _agentsConfFile);
	vector<Config> GetAgentsConfigs() const;
	LogConfig GetLogConfig() const;

private:
	const string m_agentsConfFile;
	const string m_logConfFile;
};

#endif
