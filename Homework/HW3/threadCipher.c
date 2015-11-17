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
	  printf("Creating thread %d\n", i);
	  //thread calls print function, uses i as passed in value
	  rc = pthread_create(&threads[i], NULL, print, (void *) i);
	  //error handling
	  if (rc)
	  {
	   printf("Error code: %d\n",rc);
	   exit(-1);
  	}//end if
  }//end for
 pthread_exit(NULL);
}//end main


void *print(void *threadID)
{
  //now we will declare our string
  char plainText[33]= "BE SURE TO DRINK YOUR OVALTINE"
  char buffer[1024];
  printf("Inside Print, plainText = %s\n", plainText);
  buffer = strdup(plainText);
  printf("buffer: %s\n", buffer);


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


