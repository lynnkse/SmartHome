#include "../inc/Configurator.h"
#include <string>
#include <vector>
#include "../inc/Config.h"
#include "../inc/LogConfig.h"
#include "../inc/Parser_t.h"
#include "../inc/Tokenizer_t.h"
#include <iostream>

using namespace std;

Configurator::Configurator(const string& _agentsConfFile, const string& _logConfFile) : m_agentsConfFile(_agentsConfFile), m_logConfFile(_logConfFile) {}

Configurator::~Configurator(){};

vector<Config> Configurator::GetAgentsConfigs() const
{
	vector<Config> vec;	
	Parser_t parser;
	Tokenizer_t tokenizer;
	parser.ProcessFile(m_agentsConfFile);
	string s;

	while(parser.HasLines())
	{
		Config conf;
		
		while(s[0] != '[' && parser.HasLines())
		{		
			s = parser.GetNextLine();
		}

		if(!parser.HasLines())
			break;

		conf.SetData("id", s);
		
		s = parser.GetNextLine();

		while(s[0] != '[' && s.substr(0, 6) != "config")
		{		
			const vector<string>& tokens = tokenizer.GetStringTokens(s);
			vector<string>::const_iterator beg = tokens.begin();
			vector<string>::const_iterator end = tokens.end();
			--end;
			conf.SetData(*beg, *end);
			s = parser.GetNextLine();
		} 
		
		if(s.substr(0, 6) == "config")
		{
			conf.SetData("config", s.substr(9, s.size() - 9));
		}	
		vec.push_back(conf);
	}
/*
	Config conf1;
	conf1.SetData("type", "LiveLog");
	conf1.SetData("id", "live-log");
	conf1.SetData("From", "All");
	conf1.SetData("config", "sendtoserver:All");
	vec.push_back(conf1);
*/
	return vec;
}

LogConfig Configurator::GetLogConfig() const
{
	LogConfig conf;

	conf.SetData("port", "8888");
	conf.SetData("ip", "127.0.0.1");

	return conf;
}























































