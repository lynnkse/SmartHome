#include <map>
#include <string>

using namespace std;

class Config
{
public:
	//enum Fields {TYPE, ROOM, FLOOR, LOG, /*AGENT_LIB,*/ __NUM_OF_TYPES};

public:
	Config() {}
	~Config() {};
	//void SetData(const string& _data);
	void SetData(const string& _key, const string& _val);
	const string& GetData(const string& _key) const;
	//void SetConfig(const string& _key, const string& _val);
	//bool NeedMoreData() const;
	//const string& GetType() const;
	//const string& GetRoom() const;
	//const string& GetFloor() const;
	//const string& GetLog() const;
	const map<string, string>& GetConfig() const;

	//const string& GetAgentLibFile() const;

	//void SetType();
private:
	//string m_data[__NUM_OF_TYPES];
	map<string, string> m_data;
	//int m_currDataField;
};
