class LogConfig
{
public:
	enum Types {IP, PORT, __NUM_OF_TYPES};

public:
	LogConfig() : m_currDataField(0);
	~LogConfig();
	void SetData(const string& _data);
	const string& GetIP() const;
	const string& GetPort() const;
	
private:
	string m_data[__NUM_OF_TYPES];
	int m_currDataField;
};
