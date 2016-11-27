#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "../inc/TCPServer.h"

Server::Server(const string& _ip, int port)
{
	struct sockaddr_in serv_addr;
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
	bind(m_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(m_sockfd,5);
    clilen = sizeof(cli_addr);
}

void Server::AwaitForConnections() 
{
	while(1)
	{     
		newsockfd = accept(m_sockfd, (struct sockaddr *) &cli_addr, &clilen);
		m_sockets.push_back(newsockfd);
	}
}

void Server::SendMessage(const string& _str) const
{
	for(vector<int>::const_iterator it = m_sockets.begin(); it != m_sockets.end(); ++it)
	{
		write(*it, _str.c_str(), _str.size() + 1);
	}
}

void Server::Run()
{
	m_thread = thread([this] { AwaitForConnections(); } );
}









































