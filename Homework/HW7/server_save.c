/***********************************
 * Author: William Strouse Jr
 * Creation Date: November 9th 2015
 * Filename: server.c
 * Purpose: 
 *
 */

//#include section
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//#define section
#define michaelBuffer 1024


//int main
int main()
{
	//variable declarations
	int sockfd; //file descriptor for socket
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buf[michaelBuffer]; //buffer for message
	int n; //message size
	int clientlen; //client addr length

	//do we need a usage clause?
	
	//socket set file descriptor
	sockfd = socket(AF_INET, SOCK_DGRAM,0);
	if (sockfd < 0)
	{ error("Error opening socket");}
	
	//bind the socket 
	if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0)
	{ error("Error on binding");}
		

	//loop
	for(; ;)
	{
		//recvfrom
		clientlen = sizeof(client);
		bzero(buf, michaelBuffer);
		n = recvfrom(sockfd, buf, michaelBuffer, 0, (struct sockaddr *) &client, &clientlen);
		if (n<0)
		{ error("Error in recvfrom");

		//sendto
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &client, clientlen); 
		if (n<0)
		{ error ("ERROR in sendto");}

	
	}//end for
}//end main	





