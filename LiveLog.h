class LiveLog
{
public:
	LiveLog();
	~LiveLog();	
	void Send(const Event& _event) const;	
	void Run() const;

private:
	void operator=(const LiveLog& _log);
	void LiveLog(const LiveLog& _log);
};
