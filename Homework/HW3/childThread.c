#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//This is to test threads and all that good stuff
//Declarations:
//pid_t processID; not used in threads
#define THREADCOUNT 5 //more than just sheets
//int rc, i, x; //we will declare these in main

void *print(void *threadID); //declare the print F(x) used for each thread

int main (int argc, char *argv[])
{
	int i, rc;
	char string1 = "BE SURE TO DRINK YOUR OVALTINE";
	//char string1[33] = "BE SURE TO DRINK YOUR OVALTINE";
	//char string2[33] = "#BlameWill";

	//create the slave threads
	//we have to create the pthread_t first
	pthread_t threads[THREADCOUNT];
	for(i=0; i<THREADCOUNT; i++)
	{
	//we can do this once we have the for loop in place
	//create thread
//	rc = pthread_create(&threads[i], NULL, print, (void* )i);  
	rc = pthread_create(&threads[i], NULL, print, (void* ) string1);
	//error handling
		if(rc)
		{
		printf("ERROR #BlameWill code: %d\n", rc);
		exit(-1); 
		}//end if	
	}//end for
}//end main

void *print( void *threadID)
{
 printf("Can I print out the string? %s\n", &string1);
// printf("%d: #BlameWill: \n", threadID);
 pthread_exit(NULL);
/* char *stringInput; 
  stringInput = (char *) inputString; 
  printf("%s \n", stringInput);
 */

}//end threadOuput
