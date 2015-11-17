/***********************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: November 27, 2000
 * Modified Date: August 29, 2015
 * Filename: tcpserv.c
 * Purpose: Server example for TCP Sockets; receives one string at a time
 * Adapted from Haviland book
 *
 **********************************************************************************/ 

#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <time.h> //necessary for gettimeofday functionality
#include <stdio.h> //debugging

#define SIZE sizeof(struct sockaddr_in)


void catcher(int sig);
int newsockfd;


int main()
{
  int sockfd;
  char c;
  int pid;
  int i, numChild = 0;
  struct sockaddr_in server = {AF_INET, htons(55910), INADDR_ANY};
  static struct sigaction act;
  //added time measurement mechanism 
  //this was demonstrated on 
  //http://www.cs.loyola.edu/~jglenn/702/S2008/Projects/P3/time.html
  struct timeval startTimer;
  struct timeval stopTimer;
     

  act.sa_handler = catcher;
  sigfillset(&(act.sa_mask));
  sigaction(SIGPIPE, &act, NULL);

  //start socket descriptor timer
  gettimeofday(&startTimer, NULL); 
  // set up the transport end point
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket call failed");
      exit(-1);
    }   // end if 
  // end socket descriptor timer
  gettimeofday(&stopTimer, NULL);
  
printf("Elapsed Socket allocation Time: %ld microseconds\n", ((stopTimer.tv_sec * 1000000 + stopTimer.tv_usec) - (startTimer.tv_sec * 1000000 + startTimer.tv_usec))); 

  gettimeofday(&startTimer, NULL);
  // bind and address to the end point
  if (bind(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
      perror("bind call failed");
      exit(-1);
    }   // end if bind
  gettimeofday(&stopTimer, NULL);
  printf("Elapsed Bind Time: %ld microseconds\n", ((stopTimer.tv_sec * 1000000 + stopTimer.tv_usec) - (startTimer.tv_sec * 1000000 + startTimer.tv_usec))); 
  

  gettimeofday(&startTimer, NULL);
  // start listening for incoming connections
  if (listen(sockfd, 5) == -1)
    {
      perror("listen call failed");
      exit(-1);
    }   // end if
  gettimeofday(&stopTimer, NULL);
  printf("Elapsed Listen Time: %ld microseconds\n", ((stopTimer.tv_sec * 1000000 + stopTimer.tv_usec) - (startTimer.tv_sec * 1000000 + startTimer.tv_usec))); 
  for (;;)
    {
      // accept connection

      gettimeofday(&startTimer, NULL);
      if ((newsockfd = accept(sockfd, NULL, NULL)) == -1)
	{
	  perror("accept call failed");
	  exit(-1);
	}   // end if

      gettimeofday(&stopTimer, NULL);
      // spawn a child to deal with the connection
  printf("Elapsed Socket Acceptance Time: %ld microseconds\n", ((stopTimer.tv_sec * 1000000 + stopTimer.tv_usec) - (startTimer.tv_sec * 1000000 + startTimer.tv_usec))); 
    
   
      gettimeofday(&startTimer, NULL);
      // spawn a child to deal with the connection
      if ((pid = fork()) == -1)
     
    	{
	  perror("fork failed");
	  exit(-1);
	}   // end if

      gettimeofday(&stopTimer, NULL);    
  printf("Elapsed Connection Time: %ld microseconds\n", ((stopTimer.tv_sec * 1000000 + stopTimer.tv_usec) - (startTimer.tv_sec * 1000000 + startTimer.tv_usec))); 

      
      gettimeofday(&startTimer, NULL);
      if (pid == 0)
	{
	  str_echo(newsockfd);	/* process the request */

	  // when client is no longer sending information the
	  // socket can be closed and child process terminated
	  close(newsockfd);
	  exit(0);
	}   // end child process

      gettimeofday(&stopTimer, NULL);
  printf("Elapsed Process Time: %ld microseconds\n", ((stopTimer.tv_sec * 1000000 + stopTimer.tv_usec) - (startTimer.tv_sec * 1000000 + startTimer.tv_usec))); 
      // parent doesn't need newsockfd
      close(newsockfd);
      numChild++;
    }   // end for

  // wait for children
  for (i = 0; i < numChild; i--)
    wait();
}   // end main



void catcher(int sig)
{
  close(newsockfd);
  exit(0);
}   // end function catcher
