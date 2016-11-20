#include <vector>
#include <string>

using namespace std;

class Config;
class LogConfig;

class Configurator
{
public:
	~Configurator();
	Configurator(const string& _agentsConfFile, const string& _logConfFile);
	vector<Config> GetAgentsConfigs() const;
	LogConfig GetLogConfig() const;

private:
	const string m_agentsConfFile;
	const string m_logConfFile;
};
