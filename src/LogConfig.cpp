#include "../inc/LogConfig.h"
#include <string>
#include <iostream>

using namespace std;

LogConfig::LogConfig(){}

LogConfig::~LogConfig(){}

void LogConfig::SetData(const string& _key, const string& _val)
{
	m_data[_key] = _val;
}

const string& LogConfig::GetData(const string& _key)
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

