#ifndef __SERVER

class Server
{
public: 
	Server::Server(const string& _ip, int port);
	Server::~Server() {}
	void SendMessage(const string& _str) const;

private:
	void operator=(const Server& _serv);
	Server(const Server& _serv);
	void AwaitForConnections() const;

	vector<int> m_sockets;
	int m_sockfd
};
