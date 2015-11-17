/***********************************
 * Author: William Strouse Jr
 * Creation Date: November 9th 2015
 * Modified Date: November 10th 2015
 * Due Date: November 9th 2013
 * Course: CSC 328
 * Professor Name: Dr. Lisa Frye
 * Assigment: HW7
 * Filename: server.c client.c
 * Purpose: Write an iterative, connectionless server for the client program sockets/UDP in the course’s public directory on the acad system.
 * Turn in the server code using turnin on acad.
***********************************************************/


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
	char buf[SIZE]; //buffer for message
	int slen=sizeof(client), recvlen; //message size
	int i; 
	
	//socket set file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM,0))==-1)
	{ perror("Socket opening error");
	  return 0; 
	}
//	printf("socket opened");

	//bind the socket 	
	memset((void *)&server, 0, sizeof(server));//segfault correction
	memset((void *)&client, 0, sizeof(client));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *)&server, SIZE) ==-1)
	{ perror("Binding error");
	  return 0;
	}
//	printf("made it past the binding");
	
	//loop
//	for(i=0;i<100;i++)
	for (;;) //server infinite loop
	{
		//recvfrom
		recvlen = recvfrom(sockfd, buf, SIZE, 0, (struct sockaddr *)&client, &addrlen);
		//printf("recieved %d bytes\n", recvlen);
		if (recvlen > 0)
		{
			buf[recvlen] = 0;
			//printf("Received message: \"%s\"\n", buf);
			//convert buf to upper and send back
			//itoa(toupper(buf),buf, 10); //NOT SUPPORTED - http://www.cplusplus.com/reference/cstdlib/itoa/
//			snprintf();//this is supported
			//for loop for string length
			int i; 
			
			for (i=0; i<recvlen; i++)
			{
				//get the character and convert to upper case. 
				buf[i] = toupper(buf[i]); 
			}
			

		}
		//reply to the client with uppercase 
		sendto(sockfd,buf, strlen(buf),0,(struct sockaddr *)&client, slen);
	//	printf("Value of buf: %s\n", toupper(buf));
	}//end for

close(sockfd);
}//end main	





