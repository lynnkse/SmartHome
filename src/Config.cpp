#include <string>
#include "../inc/Config.h"

using namespace std;

//void Config::SetData(const string& _data) {} //TODO
//bool Config::NeedMoreData() const { return m_currDataField < __NUM_OF_TYPES; }
//const string& Config::GetType() const { return m_data[TYPE]; }
//const string& Config::GetRoom() const { return m_data[ROOM]; }
//const string& Config::GetFloor() const { return m_data[FLOOR]; }
//const string& Config::GetLog() const { return m_data[LOG]; }
//const string& Config::GetAgentLibFile() const { return m_data[AGENT_LIB]; }
const map<string, string>& Config::GetConfig() const {  return m_data; }
//void Config::SetConfig(const string& _key, const string& _val) { m_config[_key] = _val; }

void Config::SetData(const string& _key, const string& _val)
{
	m_data[_key] = _val;
}

const string& Config::GetData(const string& _key) const
{
	map<string, string>::const_iterator it = m_data.find(_key);
	if(it != m_data.end())
	{
		return (*it).second;
	}
	else
	{
		throw ("no such field");
	}
}
