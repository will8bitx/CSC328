i/***********************************
* Author: William Strouse Jr
* Date:  October 26th 2015
* HW5: Write a TCP client program for the Quote Of The Day (QOTD) protocol as defined by RFC 865. The hostname of the QOTD server should be passed as a command-line argument.
* Submit via turnin on acad (csit).
*
*Quote when I got it to work fully: 
*Quote Of The Day: As long as there are ill-defined goals, bizarre bugs, and unrealistic schedules, there will be Real Programmers willing to jump in and Solve The Problem, saving the documentation for later.
***********************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //resolved segfault!!
#include <netdb.h> //hostent f(x)
#define SIZE sizeof(struct sockaddr_in)

int main (int argc, char *argv[])
{
	//declare variables
	char replyIn[512], resolvedIP[100]; //QOTD per RFC865 specifies the length of QOTD message to be max 512 characters
	int sockfd, i; //socket descriptor
	struct sockaddr_in server;
	struct hostent *hostNm;  //name of the host
	struct in_addr **addr_list; //double rainbow of pointers to the address list

	server.sin_family = AF_INET; //IPV4
	server.sin_port = htons(17); //default port for QOTD

	//validate entry
	if (argc != 2) //need to have program name & hostname
	{
		//invalid entry, print useage
		printf("Useage: %s <hostname>\n", argv[0]);
	}	
	else 
	{
	//Example URL: http://www.binarytides.com/socket-programming-c-linux-tutorial
	//SEGFAULTS on the following code if the arpa/inet.h header is missing: 
		if ((hostNm = gethostbyname(argv[1])) == NULL)
		{
			//null hostname
			herror("gethostbyname");
			exit(-1);
		}	
		//Cast the h_addr_list into in_addr
		//printf("Official name is: %s\n", hostNm->h_name);
		//printf("IP Addresses: ");
		addr_list = (struct in_addr **) hostNm->h_addr_list;
		for (i = 0; addr_list[i] != NULL; i++)
		{
			//return the first one;
			strcpy(resolvedIP, inet_ntoa(*addr_list[i]));
			//printf("%s ", inet_ntoa(*addr_list[i]));
		}	
		printf("%s resolved to %s\n", hostNm->h_name, resolvedIP);
	
		//Assign resolved IP to the sin_addr!
		server.sin_addr.s_addr = inet_addr(resolvedIP);

		//transport setup
		if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
		{
			perror("socket call failed");
			exit(-1);
		} //enf if
		
		//connect socket
		if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
		{
			perror("connect call failed");
			exit(-1);
		}//end if

		//gedt quote of the day
		//recv(int sockfd, void *buf, size_t len, int flags);
		if (recv(sockfd, replyIn, 512, 0) < 0)
		{
			printf("Receive failed");
			exit(-1);
		} 
		//print quote of the day
		printf("%c[1;31m", 27); //fancy red/pink color
		printf("Quote Of The Day: %s\n", replyIn);
		printf("%c\e[0m\n"); //clear out colors to prevent riots

	}

}//end main



