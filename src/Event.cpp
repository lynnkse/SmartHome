#include <string>
#include "../inc/Event.h"
//#include <iostream>//for test
//using namespace std;

Event::Event(const time_t& _timestamp, const string& _type, const string& _data, const string& _location, const string& _log) : m_timestamp(_timestamp), m_type(_type), m_data(_data), m_location(_location), m_log(_log) {}
Event::~Event(){};
const string& Event::GetType() const { return m_type; }
const string& Event::GetData() const { return m_data; }
const string& Event::GetLocation() const { return m_location; } 
const string& Event::GetLog() const { return m_log; }
