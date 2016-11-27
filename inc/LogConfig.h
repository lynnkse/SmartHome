#ifndef __LOGCONFIG_H__
#define __LOGCONFIG_H__

#include <map>

using namespace std;

class LogConfig
{
public:
	LogConfig();
	~LogConfig();
	void SetData(const string& _key, const string& _val);
	const string& GetData(const string& _key);
	
private:
	map<string, string> m_data;
};

#endif
