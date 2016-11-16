#include <map>

class Config
{
public:
	enum Fields {TYPE, ROOM, FLOOD, LOG, CONFIG, __NUM_OF_TYPES};

public:
	Config() : m_currDataField(0) {};
	~Config();
	SetData(const string& _data);
	const string& GetType();
	const string& GetRoom();
	const string& GetFloor();
	const string& GetLog();
	const string& GetConfig();
private:
	string[_NUM_OF_TYPES] m_data;
	int m_currDataField;
};
