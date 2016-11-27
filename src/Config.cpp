#include <string>
#include "../inc/Config.h"
#include <iostream>

using namespace std;

const map<string, string>& Config::GetConfig() const {  return m_data; }

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
