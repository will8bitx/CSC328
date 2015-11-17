/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: November 27, 2000
 * Modified Date: August 29, 2015
 * Filename: tcpcli.c
 * Purpose: Client example for TCP Sockets; sends one string at a time 
 * Adapted from Haviland book
 *
 **********************************************************************************/ 

#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE sizeof(struct sockaddr_in)
//#define IPADDR   "127.0.0.1"  // localhost
#define IPADDR   "156.12.127.18"  // csit
//#define IPADDR   "156.12.127.9"   // harry
//#define IPADDR   "156.12.127.10"  // hermione

int main()
{
  int sockfd;
  char c, rc;
  struct sockaddr_in server;


  server.sin_family = AF_INET;
  server.sin_port = htons(55910);
  // convert and store the server's IP address
  server.sin_addr.s_addr = inet_addr(IPADDR);
  
  // set up the transport end point
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket call failed");
      exit(-1);
    }   // end if

  // connect the socket to the server's address
  if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
      perror("connect call failed");
      exit(-1);
    }   // end if

  str_cli("Hello World!\n", sockfd);		/* do it all */

}  // end main
