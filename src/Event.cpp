#include <string>
#include "../inc/Event.h"
//#include <iostream>//for test
//using namespace std;

Event::Event(time_t _timestamp, string _type, string _data, string _location) : m_timestamp(_timestamp), m_type(_type), m_data(_data), m_location(_location) 
{ /*cout << "Event : Event created" << endl;*/}
Event::~Event(){};
const string& Event::GetType() const { return m_type; }
const string& Event::GetData() const { return m_data; }
const string& Event::GetLocation() const { return m_location; } 
