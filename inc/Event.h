#include <ctime>
#include <string>
#include <ctime>

using namespace std;

class Event
{
public:
	Event(const time_t& _timestamp, const string& _type, const string& _data, const string& _location, const string& _log);
	~Event();
	const string& GetType() const;
	const string& GetData() const;
	const string& GetLocation() const;
	const string& GetLog() const;
	const string GetTime() { return ctime(&m_timestamp); };

private:
	time_t m_timestamp;
	string m_type;
	string m_data;
	string m_location;
	string m_log;
};
