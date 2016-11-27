#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <thread>

using namespace std;

class Server
{
public: 
	Server(const string& _ip, int port);
	~Server() {}
	void SendMessage(const string& _str) const;
	void Run();

private:
	void operator=(const Server& _serv);
	Server(const Server& _serv);
	void AwaitForConnections();

	vector<int> m_sockets;
	int m_sockfd;
	int newsockfd;
	socklen_t clilen;
	struct sockaddr_in cli_addr;
	thread m_thread;
};

#endif
