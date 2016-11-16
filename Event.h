#include <ctime>

class Event
{
public:
	Event(time_t _timestamp, string _type, string _data, string _location);
	~Event();

private:
	time_t m_timestamp;//TODO ???
	string m_type;
	string m_data;
	string m_location;
};
