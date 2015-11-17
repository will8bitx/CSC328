/***********************************
*
*
*
***********************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE sizeof(struct sockaddr_in)

int main (int argc, char *argv[])
{


//declare variables
char QOTD[512]; //QOTD per RFC865 specifies the length of QOTD message to be max 512 characters
int sockfd; //socket descriptor
struct sockaddr_in server;
 
//bind socket
server.sin_family = AF_INET;
server.sin_port = htons(17); //I want to user getservicebyportname() here as hardcoding is BAD
//server.sin.addr.s_addr = inet_addr(argv[1]); //command line argument used. Need to validate hostname
server.sin.addr.x_addr = inet_addr("139.162.154.113"); //hardcoded for testing


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

//validate entry
if (argc != 1) //need to have program name & hostname
{
	//invalid entry, print useage
	printf("Useage: %s <hostname>\n", argv[0]);
}
else 
{
	//get quote of the day
	//recv(int sockfd, void *buf, size_t len, int flags);
	if (recv(sockfd, QOTD, 512, 0) < 0)
	{
	 printf("Receive failed");
	} 
	//print quote of the day
	printf("QOTD: %d\n", QOTD);
}

}//end main


//exit

