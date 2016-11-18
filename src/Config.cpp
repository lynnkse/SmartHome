#include <string>
#include "../inc/Config.h"

using namespace std;

void Config::SetData(const string& _data) {} //TODO
bool Config::NeedMoreData() const { return m_currDataField < __NUM_OF_TYPES; }
const string& Config::GetType() const { return m_data[TYPE]; }
const string& Config::GetRoom() const { return m_data[ROOM]; }
const string& Config::GetFloor() const { return m_data[FLOOR]; }
const string& Config::GetLog() const { return m_data[LOG]; }
const string& Config::GetConfig() const { return m_data[CONFIG]; }
const string& Config::GetAgentLibFile() const { return m_data[AGENT_LIB]; }
