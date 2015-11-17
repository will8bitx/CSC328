/**************************************************************************
 * Author: William Strouse Jr
 * Creation Date: September 21st 2015
 * Due Date: September 21st 2015
 * Course: CSC328 Network Programming
 * Professor Name: Dr. Frye
 * Assignment: HW3
 * Filename: threadTest_WS.c
 * Purpose: This program will create 5 slave threads from a single
 * master program and display text to the screen from each thread.
 * Functionality has been extended to apply a Ceaser Cipher to the 
 * text shifting the characters displayed by the ID of the thread
 * executing.
 *
 * Compiler instructions: gcc -o threadTest_WS threadTest_WS.c -lpthread
 * ***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define THREADCOUNT 5

//function declaration
void *print(void *threadID); //pointing the function with a deallocated ID


int main(int argc, char *argv[])
{
  //here we declare variables and init the threads
  int i, rc;
  pthread_t threads[THREADCOUNT];
  //begin for loop for calling the thread
  for(i=0; i<THREADCOUNT; i++)
  {
	  //printf("Creating thread %d\n", i);
	  //thread calls print function, uses i as passed in value
	  rc = pthread_create(&threads[i], NULL, print, (void *)i);
	  //error handling
	  if (rc)
	  {
	   printf("Error code: %d\n",rc);
	   exit(-1);
  	}//end if
  }//end for
 pthread_exit(NULL);
}//end main

/****************************************
 * Print Function
 * void *print(void *threadID)
 * Purpose: Called from the thread create,
 * this function encrypts plain text
 * messages by shifting the output by
 * the value of the threadID passed in
 * by the pthread_create call. 
 * 
 * Parameters: *threadID is used as the
 * key to the cipherText, so you subtract
 * each letter by that threadID and you
 * will decrypt the message. Special 
 * consideration had to be paid because
 * threadID starts off as 0.
 * 
 * Notes: Tried to pull off using rand() 
 * for a randomly generated key, but 
 * rand() is not thread safe. Saves the
 * seed values in the state, and the threads
 * executed so quickly the time_t seed was
 * not able to generate enough of a random
 * number to matter. Where this did work 
 * was by putting a unique key on each 
 * member of the character array. Quickly
 * realized that was great but I had no key
 * to decypher. 
 *
 * ***************************************/
void *print(void *threadID)
{
  //now we will declare our string
  char plainText[33]= "BE SURE TO DRINK YOUR OVALTINE";
  char secretMessage[375] = "In 1972, a crack commando unit was sent to prison by a military court for a crime they didn't commit. These men promptly escaped from a maximum security stockade to the Los Angeles underground. Today, still wanted by the government they survive as soldiers of fortune. If you have a problem, if no one else can help, and if you can find them....maybe you can hire The A-Team.";
  //char buffer[1024];
  //printf("Inside Print, plainText = %s\n", plainText);
  //printf("&threadID: %d\n", &threadID);
  //printf("threadID: %d\n", threadID);
  //  buffer = strdup(plainText); //internet was wrong
  //  printf("buffer: %s\n", buffer);
  //create Cipher Text
  char cipherText[375]; //cheating by knowing the length of the string
  int x; //there is probably a better way to do this...
//  time_t t; //used for creating random seed
//  srand((unsigned) time(&t)); //init random number generator
//  int key = rand() % 26;//not thread safe!! Should use drand48_r instead
  for (x=0; x<strlen(secretMessage); x++)
  {
	
	//we need to increment threadID  for 0 values
	if (threadID == 0)
	{  threadID = 26;}
	else if (threadID >26 )
	{ threadID = (int)threadID % 26; } //every value over 26 must wrap around 
	
  	//printf("ThreadID = %d\n", threadID);
	//cipherText[x] = plainText[x]+threadID; //increment the cipher with the number of times the thread is called.
	cipherText[x] = secretMessage[x]+threadID;
//	cipherText[x] = plainText[x]+rand()% 26;//better strength cipher on each letter, but not what I was trying to do. 
	//cipherText[x] = plainText[x]+key; //ran out of time to make the random work properly
  }//end for 
  if (threadID == 26){threadID = 0;}
  printf("\n\nThreadID: %d cipherText: %s\n", threadID, cipherText);//this gives away our cipher, will hide this by using rand() for the shift. 

pthread_exit(NULL); //undefined reference to 'pthread_create' error - actually that was resolved by -lpthread in the command line.

}//end void


/*unused/unfit code
//This is to test threads and all that good stuff
//Declarations:
//pid_t processID; //only used for fork, not threads
//int rc, i, x;
//char string1[33] = "BE SURE TO DRINK YOUR OVALTINE"; //we do not want to declare this globally

//create the slave threads
//we have to create the pthread_t first
pthread_t thread1;
rc = pthread_create(&thread1, 
*/


