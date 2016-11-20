#ifndef __LOGCONFIG_H__
#define __LOGCONFIG_H__

#include <map>

using namespace std;

class LogConfig
{
public:
	//enum Types {IP, PORT, __NUM_OF_TYPES};

public:
	LogConfig();
	~LogConfig();
	void SetData(const string& _key, const string& _val);
	const string& GetData(const string& _key);
	
private:
	//string m_data[__NUM_OF_TYPES];
	//int m_currDataField;
	map<string, string> m_data;
};

#endif
