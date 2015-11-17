/***********************************
 * Author: William Strouse Jr
 * Creation Date: November 9th 2015
 * Filename: server.c
 * Purpose: 
 *
 */

//#include section
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#define section
#define SIZE sizeof(struct sockaddr_in)
#define PORT 50018


//int main
int main(void)
{
	
	//variable declarations
	int sockfd; //file descriptor for socket
	struct sockaddr_in server = {AF_INET, htons(50018),INADDR_ANY};//taken form tcpserv
	struct sockaddr_in client;
	socklen_t addrlen = sizeof(client);
	unsigned char buf[SIZE]; //buffer for message
	int slen=sizeof(client), recvlen; //message size
	int i; 
	
//do we need a usage clause?
	//socket set file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM,0))==-1)
	{ error("Error opening socket");}
//	printf("socket opened");
	//clear out the memory
//	memset((char *)&server, 0, sizeof(server)); //imcompatible implicit declaration error
	//set the server address	
//	server.sin_family = AF_INET;
//	server.sin_port = htons(PORT);
//	server.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind the socket 	
	memset((void *)&server, 0, sizeof(server));//segfault correctioni
	memset((void *)&client, 0, sizeof(client));
	if (bind(sockfd, (struct sockaddr *)&server, SIZE) ==-1)
	{ error("Error on binding");}
//	printf("made it past the binding");
	
	//loop
	for(i=0;i<100;i++)
	{
		//recvfrom
		printf("waiting on port %d\n", PORT);
		//printf("sockfd: %d\n", sockfd);
		//printf("buf: %s\n", buf);
		//printf("size: %d\n", SIZE);
		recvlen = recvfrom(sockfd, buf, SIZE, 0, (struct sockaddr *)&client, &addrlen);
//		if(recvfrom(sockfd, buf, SIZE, 0, (struct sockaddr *)&client, &slen) ==-1)
//		{printf("Error");}
		printf("recieved %d bytes\n", recvlen);
		if (recvlen > 0)
		{
			buf[recvlen] = 0;
			printf("Received message: \"%s\"\n", buf);
		}
		//sendto(sockfd, buf, strlen(buf),0,(struct sockaddr *)&client, slen);
		printf("Value of i: %d\n", i);
	}//end for

close(sockfd);
}//end main	





