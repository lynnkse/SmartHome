#include <ctime>
#include <string>

using namespace std;

class Event
{
public:
	Event(time_t _timestamp, string _type, string _data, string _location);
	~Event();
	const string& GetType() const;
	const string& GetData() const;
	const string& GetLocation() const;

private:
	time_t m_timestamp;
	string m_type;
	string m_data;
	string m_location;
};
