#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "../inc/TCPServer.h"

Server::Server(const string& _ip, int port)
{
	int newsockfd, portno;
    socklen_t clilen;
	struct sockaddr_in serv_addr;//, cli_addr;
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
	bind(m_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd,5);
    clilen = sizeof(cli_addr);
}

void Server::AwaitForConnections() const
{
     //int sockfd, newsockfd, portno;
     //socklen_t clilen;
     //char buffer[256];
     //struct sockaddr_in serv_addr, cli_addr;
     //int n;
     //if (argc < 2) {
     //    fprintf(stderr,"ERROR, no port provided\n");
     //    exit(1);
     //}
     //sockfd = socket(AF_INET, SOCK_STREAM, 0);
     //if (sockfd < 0) 
     //   error("ERROR opening socket");
     //bzero((char *) &serv_addr, sizeof(serv_addr));
     //portno = atoi(argv[1]);
     //serv_addr.sin_family = AF_INET;
     //serv_addr.sin_addr.s_addr = INADDR_ANY;
     //serv_addr.sin_port = htons(portno);
     //if (bind(sockfd, (struct sockaddr *) &serv_addr,
     //        sizeof(serv_addr)) < 0) 
     //         error("ERROR on binding");
     //listen(sockfd,5);
     //clilen = sizeof(cli_addr);
     newsockfd = accept(m_sockfd, (struct sockaddr *) &cli_addr, &clilen);
	
	 m_sockets.insert(newsockfd);

     /*bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);*/
     return 0; 
}

void Server::SendMessage(const string& _str) const
{
	for(set<int>::iterator it = m_sockets.begin(); it != m_sockets.end(); ++it)
	{
		write(*it, _str.c_str(), _str.size() + 1);
	}
}









































