#include "../inc/Configurator.h"
#include <string>
#include <vector>
#include "../inc/Config.h"
#include "../inc/LogConfig.h"
#include "../inc/Parser_t.h"
#include "../inc/Tokenizer_t.h"
#include <iostream>

using namespace std;

Configurator::Configurator(const string& _agentsConfFile) : m_agentsConfFile(_agentsConfFile){}

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
	return vec;
}























































