#include <map>

class Config
{
public:
	enum Fields {TYPE, ROOM, FLOOD, LOG, CONFIG, AGENT_LIB, __NUM_OF_TYPES};

public:
	Config() : m_currDataField(0) {}
	~Config();
	void SetData(const string& _data);
	bool NeedMoreData() const;
	const string& GetType() const;
	const string& GetRoom() const;
	const string& GetFloor() const;
	const string& GetLog() const;
	const string& GetConfig() const;
	const string& GetAgentLibFile() const;
private:
	string m_data[__NUM_OF_TYPES];
	int m_currDataField;
};
